# Zoom
Zoo Markup: Fast &amp; modern C++ header-only HTML/XML document generator. Work in progress.

## Todo
* Helper methods for commonly needed tags (div, span, p, link, title)
* Binding external data, variables

Example usage:
```c++
#include <iostream>
#include "zoo.h"

using namespace zoo;
int main() {
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
	std::cout << doc.toString();
}
```
produces the following output:
```html
<!DOCTYPE html>
<html>
<head></head>
<body>
  <header>
    <h1>Hello World</h1>
  </header>
  <content>
    <b>this is bold text</b>
    <i>this is italic text</i>
  </content>
</body>
</html>
```
