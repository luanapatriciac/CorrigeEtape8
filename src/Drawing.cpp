#include "Drawing.h"

Drawing::Drawing(pugi::xml_node node)
	: group{ "root (member of Drawing)", 0, 0, node }
{
}

void Drawing::print(std::ostream & stream) const
{
	group.print(stream, "", 0, 0);
}

void Drawing::draw(SFML_output & out) const
{
	group.draw(out, 0, 0);
}

std::ostream & operator<<(std::ostream & stream, Drawing const & d)
{
	d.print(stream);
	return stream;
}
