#pragma once
#include <memory>
#include <list>
#include <string>
#include <sstream>
#include <unordered_map>

namespace zoo {

	class Element {
	public:
		virtual std::string toString() const = 0;
	};

	class Text : public Element {
		std::string text;
	public:
		Text(const std::string& text) : text{ text } {}
		std::string toString() const override {
			return text;
		}
	};

	class Tag : public Element {
		std::list<std::shared_ptr<Element>> contents;
		std::string tag;
		std::unordered_map<std::string, std::string> attributes;
	public:
		Tag(const std::string& tag) : tag{ tag }, contents{}, attributes{} {}

		template <typename... Ts>
		Tag(const std::string& tag, const Ts&&... tail) : tag{ tag }, attributes{} {
			for (auto e : { tail... }) {
				add(std::move(e));
			}
		}

		virtual std::string toString() const override {
			std::ostringstream out;
			out << '<' << tag;
			for (auto a : attributes) {
				out << ' ' << a.first << "=\"" << a.second << "\"";
			}
			out << '>';
			for (auto e : contents) {
				out << e->toString();
			}
			out << "</" << tag << '>';
			return out.str();
		}

		void setAttribute(const std::string& name, const std::string& attribute) {
			attributes[name] = attribute;
		}

		template<typename T>
		T* add(const T&& element) {
			contents.emplace_back(std::make_shared<T>(element));
			return static_cast<T*>(contents.back().get());
		}


	};

	class HTMLDocument : public Tag {

		class DocType : public Element {
			std::string doctype;
		public:
			DocType(const std::string& doctype) : doctype{ "<!DOCTYPE " + doctype + ">" } {}
			std::string toString() const override {
				return doctype;
			}
		};

		DocType doctype;
		Tag* head;
		Tag* body;

	public:
		HTMLDocument() : Tag{ "html" },
			doctype{ "html" },
			head{ Tag::add(Tag{ "head" }) },
			body{ Tag::add(Tag{ "body" }) } {}

		std::string toString() const override {
			return doctype.toString() + Tag::toString();
		}

		template<typename T>
		T* add(const T&& element) {
			return body->add(std::move(element));
		}


	};

}
