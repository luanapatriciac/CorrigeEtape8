#include <iostream>
#include "myMain.h"
#include "Drawing.h"
#include "SFML_output.h"

int myMain()
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file("visage.xml");
	if (!result)
	{
		std::cerr << "Could not open file visage.xml" << std::endl;
		return 1;
	}

	Drawing d(doc.child("Drawing"));
	std::cout << d;

	SFML_output out;
	d.draw(out);
	out.display();

	return 0;
}
