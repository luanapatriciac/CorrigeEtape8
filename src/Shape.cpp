#include "Shape.h"

static int rank = 0;

Shape::Shape(std::string label, double x, double y)
	: label{ label }
	, x{ x }
	, y{ y }
{
}

Shape::~Shape()
{
}

std::string Shape::get_label() const
{
	return label;
}

double Shape::get_x() const
{
	return x;
}

double Shape::get_y() const
{
	return y;
}

void Shape::print(std::ostream &stream, std::string indent, double x_origin, double y_origin, std::string const& shape_type) const
{
		stream << "#" << rank << " : " << indent << shape_type;
		++rank;
		stream << " \"" << label << "\" / absolute=(" << x_origin + x << "," << y_origin + y << ") / relative=(" << x << "," << y << ")";
	}

void Shape::compute_absolute_xy(double x_origin, double y_origin, std::map<std::string, std::pair<double, double>> &s2pair) const
{
	s2pair[label] = std::make_pair(x_origin + x, y_origin+ y);
}
