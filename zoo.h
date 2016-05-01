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

		template <typename T>
		Tag(const std::string& tag, const T& element) :
			tag{ tag }, attributes{} {
			add_front(std::move(element));
		}

		template <typename T, typename... Ts>
		Tag(const std::string& tag, const T& element, const Ts&... elements) :
			Tag(tag, elements...) {
			add_front(std::move(element));
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

		template<typename T>
		T* add_front(const T&& element) {
			contents.emplace_front(std::make_shared<T>(element));
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
		Tag* head_tag, body_tag;

	public:
		HTMLDocument() : Tag{ "html" },
			doctype{ "html" },
			head_tag{ add(Tag{ "head" }) },
			body_tag{ add(Tag{ "body" }) } {}

		std::string toString() const override {
			return doctype.toString() + Tag::toString();
		}


		template <typename T>
		void body(const T&& element) {
			body_tag->add(std::move(element));
		}

		template <typename T, typename... Ts>
		void body(const T&& element, const Ts&&... elements) {
			body(std::move(elements...));
			body_tag->add_front(std::move(element));
		}

		template <typename T>
		void head(const T&& element) {
			head_tag->add(std::move(element));
		}

		template <typename T, typename... Ts>
		void head(const T&& element, const Ts&&... elements) {
			head(std::move(elements...));
			head_tag->add_front(std::move(element));
		}

	};

	class Title : public Tag {
	public:
		template <typename... Ts>
		Title(const Ts&&... elements) : Tag("title", elements...){}
	};

	class Div : public Tag {
	public:
		template <typename... Ts>
		Div(const Ts&&... elements) : Tag("div", elements...) {}
	};

	class H1 : public Tag {
	public:
		template <typename... Ts>
		H1(const Ts&&... elements) : Tag("h1", elements...) {}
	};

	class H2 : public Tag {
	public:
		template <typename... Ts>
		H2(const Ts&&... elements) : Tag("h2", elements...) {}
	};

	class Strong : public Tag {
	public:
		template <typename... Ts>
		Strong(const Ts&&... elements) : Tag("strong", elements...) {}
	};
	class Ul : public Tag {
	public:
		template <typename... Ts>
		Ul(const Ts&&... elements) : Tag("ul", elements...) {}
	};
	class Li : public Tag {
	public:
		template <typename... Ts>
		Li(const Ts&&... elements) : Tag("li", elements...) {}
	};
}
