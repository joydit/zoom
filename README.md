# Zoom
Zoo Markup: Fast &amp; modern C++ header-only HTML/XML document generator. Work in progress.

## Todo
* Helper methods for commonly needed tags (div, span, p, link, title) and constructors for those tags that accept a ```std::string``` as an argument.
* Binding external data, variables

Example usage:
```c++
#include <iostream>
#include "zoo.h"

using namespace zoo;
int main() {
	HTMLDocument doc;
	doc.head(
		Title(Text("Hello World" )));
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
	std::cout << doc.toString();
}
```
produces the following output:
```html
<!DOCTYPE html>
<html>
    <head>
        <title>Hello World</title>
    </head>
    <body>
        <div>
            <h1>Heading</h1>
            <h2>Subheading</h2>
        </div>
        <div>
            <div>
                <strong>a list</strong>
            </div>
            <ul>
                <Li>item 1</Li>
                <Li>item 2</Li>
                <Li>item 3</Li>
            </ul>
        </div>
    </body>
</html>
```
