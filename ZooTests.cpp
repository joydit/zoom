#define CATCH_CONFIG_MAIN
#include "catch.hpp" //requires Catch
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
	doc.add(Tag{ "header",
		Tag{ "h1",
			Text{"Hello World"}}});

	doc.add(Tag{ "content",
		Tag{"b",
			Text{"this is bold text"}},
		Tag{"i",
			Text{"this is italic text"}}
	});
	REQUIRE(doc.toString() == "<!DOCTYPE html><html><head></head><body><header><h1>Hello World</h1></header><content><b>this is bold text</b><i>this is italic text</i></content></body></html>");

}

