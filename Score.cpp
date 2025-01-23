#include "Score.h"

Font font;

void loadFont()
{
    if (!font.openFromFile("resources\\ShortBaby.ttf"))
        throw std::exception("Couldn't load ShortBaby font");
}

Score::Score() :
    Text(font, "0"),
    score{ 0 }
{}

Score& Score::operator++(int)
{
    score++;
    setString(std::to_string(score));
    return *this;
}
