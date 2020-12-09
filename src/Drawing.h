#pragma once
#include "Group.h"
#include "SFML_output.h"

class Drawing
{
public:
	Drawing(pugi::xml_node node);
	void print(std::ostream &stream) const;
	void draw(SFML_output & out) const;
private:
	Group group;
};
std::ostream &operator<<(std::ostream &stream, Drawing const& d);

