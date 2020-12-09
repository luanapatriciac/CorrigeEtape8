#pragma once
#include <SFML/Graphics.hpp>
class SFML_output
{
public:
	SFML_output();
	void draw_circle(double absolute_x, double absolute_y, double r, std::string color);
	void display();
	void clean();

private:
	sf::Color string2color(std::string const &s);
	sf::RenderWindow window;
};

