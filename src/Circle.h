#pragma once
#include <string>
#include "pugixml.hpp"
#include "Shape.h"

class Circle :
	public Shape 
{
public:
	Circle(std::string label, double x, double y, double r, std::string color);
	Circle(pugi::xml_node node);
	double get_r();
	std::string get_color();
	void print(std::ostream & stream, std::string indent, double x_origin, double y_origin) const override;
	void draw(SFML_output & out, double x_origin, double y_origin) const override;

private:
	double r;
	std::string color;
};

