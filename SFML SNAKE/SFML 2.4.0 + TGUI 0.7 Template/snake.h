#pragma once
#include <SFML/Graphics.hpp>
class snake
{
public:
	sf::Vector2u shape[1600];
	int direction;
	int length;
	snake();
	~snake();
};

