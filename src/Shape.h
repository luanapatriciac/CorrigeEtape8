#pragma once
#include <string>
#include <map>
#include "SFML_output.h"

class Shape
{
public:
	Shape(std::string label, double x, double y);
	virtual ~Shape() =0;
	std::string get_label() const;
	double get_x() const;
	double get_y() const;
	virtual void print(std::ostream &stream, std::string indent, double x_origin, double y_origin, std::string const& shape_type) const;
	virtual void print(std::ostream &stream, std::string indent, double x_origin, double y_origin) const =0;
	virtual void draw(SFML_output & out, double x_origin, double y_origin) const =0;
	// For unit tests, computes the absolute (x,y) of the shape and stores it in s2pair with key label
	virtual void compute_absolute_xy(double x_origin, double y_origin, std::map<std::string,std::pair<double,double>> &s2pair) const;
protected:
	double x;
	double y;
private:
	std::string label;
};

