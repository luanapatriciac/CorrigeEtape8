#pragma once
#include <vector>
#include <memory>
#include  "pugixml.hpp"
#include  "Shape.h"

class Group :
	public Shape
{
public:
	Group(std::string label, double x, double y);
	Group(pugi::xml_node node);
	Group(std::string label, double x, double y, pugi::xml_node node);
	void compute_absolute_xy(double x_origin, double y_origin, std::map<std::string, std::pair<double, double>> &s2pair) const override;
	void add(std::unique_ptr<Shape> shape);
	std::vector<std::unique_ptr<Shape>> & get_children();
	virtual void print(std::ostream &stream, std::string indent, double x_origin, double y_origin) const override;
	void draw(SFML_output & out, double x_origin, double y_origin) const override;
private:
	std::vector<std::unique_ptr<Shape>> children;
};

