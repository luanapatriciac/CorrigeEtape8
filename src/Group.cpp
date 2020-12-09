#include <assert.h>
#include <string_view> // string_view requires C++17 ==> In Visual Studio, /Project properties -> Configuration properties -> C/C++ -> Language -> C++ Language standard/ and select "ISO C++ 17 Standard"
#include <memory>
#include "Group.h"
#include "Circle.h"

using namespace std::literals; // For having syntax: "Circle"sv 

Group::Group(std::string label, double x, double y)
	: Shape{ label, x, y }
{
}

Group::Group(pugi::xml_node node)
	: Group{ node.attribute("label").value(), node.attribute("x").as_double(), node.attribute("y").as_double(), node }
{
}

Group::Group(std::string label, double x, double y, pugi::xml_node node)
	: Group(label, x, y)
{
	for (auto child : node.children())
	{
		assert((child.name() == "Circle"sv) || (child.name() == "Group"sv)); // "Circle"sv" equivalent to std::string_view{"Circle"} thanks to: using namespace std::literals;
		if (child.name() == "Circle"sv)
			add(std::make_unique<Circle>(child));
		else // child.name() == "Group"sv
			add(std::make_unique<Group>(child));
	}
}

void Group::compute_absolute_xy(double x_origin, double y_origin, std::map<std::string, std::pair<double, double>>& s2pair) const
{
	Shape::compute_absolute_xy(x_origin, y_origin, s2pair);
	for (auto const& child : children)
	{
		child->compute_absolute_xy(x_origin + get_x(), y_origin + get_y(), s2pair);
	}
}

void Group::print(std::ostream & stream, std::string indent, double x_origin, double y_origin) const
{
	Shape::print(stream, indent, x_origin, y_origin, "Group");
	stream << std::endl;
	for (auto const& child : children)
	{
		child->print(stream, indent + "  ", x_origin + get_x(), y_origin + get_y());
	}
}

void Group::draw(SFML_output & out, double x_origin, double y_origin) const
{
	for (auto const &child : children)
	{
		child->draw(out, x_origin + x, y_origin + y);
	}
}

void Group::add(std::unique_ptr<Shape> shape)
{
	children.push_back(std::move(shape));
}

std::vector<std::unique_ptr<Shape>> & Group::get_children()
{
	return children;
}
