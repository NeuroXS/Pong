#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

extern Font font;
void loadFont();

class Score : public Text
{
public:
	Score();

	Score& operator++(int);

	unsigned int score;
};

