#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "zoo.h"

using namespace zoo;

TEST_CASE("Nodes can be created") {
	Tag node("node");
	REQUIRE(node.toString() == "<node></node>");
}

TEST_CASE("Documents can be created") {
	HTMLDocument doc;
	REQUIRE(doc.toString() == "<!DOCTYPE html><html><head></head><body></body></html>");
}

TEST_CASE("Nodes can be modified") {
	Tag p{ "p" };

	SECTION("Adding elements to nodes") {
		p.add(Text{ "Hello World" });
		REQUIRE(p.toString() == "<p>Hello World</p>");
		p.add(Text{ "Goodbye World" });
		REQUIRE(p.toString() == "<p>Hello WorldGoodbye World</p>");

		p.add(Tag{ "b" })->add(Text{ "bold text" });
		REQUIRE(p.toString() == "<p>Hello WorldGoodbye World<b>bold text</b></p>");

	}

	SECTION("Adding attributes to node") {
		p.setAttribute("style", "color:blue;");
		REQUIRE(p.toString() == "<p style=\"color:blue;\"></p>");
		p.setAttribute("class", "sometext");
		REQUIRE(p.toString() == "<p style=\"color:blue;\" class=\"sometext\"></p>");

	}
}

TEST_CASE("Documents can be modified") {
	HTMLDocument doc;
	doc.head(
		Tag( "title",
			Text("Hello World" )));
	doc.body(
		Div(
			H1(Text("Heading")),
			H2(Text("Subheading"))),
		Div(
			Div(Strong(Text("a list"))),
			Ul(
				Li(Text("item 1")),
				Li(Text("item 2")),
				Li(Text("item 3")))));

	REQUIRE(doc.toString() == "<!DOCTYPE html><html><head><title>Hello World</title></head><body><div><h1>Heading</h1><h2>Subheading</h2></div><div><div><strong>a list</strong></div><ul><li>item 1</li><li>item 2</li><li>item 3</li></ul></div></body></html>");

}

