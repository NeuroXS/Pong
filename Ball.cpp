#include "Ball.h"
#include "CONSTANTS.h"

Ball::Ball() 
	:
	CircleShape(RADIUS),
	velocity{ BALL_VELOCITY , BALL_VELOCITY}
{
	setOutlineThickness(1.f);
	setOutlineColor(sf::Color::Green);
	setPosition({ (WIDTH / 2) - RADIUS, (HEIGHT / 2) - RADIUS });
}

void Ball::moveBall()
{
	move(velocity);
}

void Ball::reset()
{
	setPosition({ (WIDTH / 2) - RADIUS, (HEIGHT / 2) - RADIUS });
}