#include "Circle.h"

Circle::Circle(std::string label, double x, double y, double r, std::string color)
	: Shape{ label, x, y }
	, r{ r }
	, color{ color }
{
}
Circle::Circle(pugi::xml_node node)
	: Circle{ node.attribute("label").value(), node.attribute("x").as_double(), node.attribute("y").as_double(), node.attribute("r").as_double(), node.attribute("color").value() }
{
}

double Circle::get_r()
{
	return r;
}

std::string Circle::get_color()
{
	return color;
}

void Circle::print(std::ostream & stream, std::string indent, double x_origin, double y_origin) const
{
	Shape::print(stream, indent, x_origin, y_origin, "Circle");
	stream << " / r=" << r << " / color=\"" << color << "\"" << std::endl;
}

void Circle::draw(SFML_output & out, double x_origin, double y_origin) const
{
	out.draw_circle(x_origin + x, y_origin + y, r, color);
}
