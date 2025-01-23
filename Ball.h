#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Ball : public CircleShape
{
public:
	Ball();
	void moveBall();
	void reset(); 

	Vector2f velocity;
};

