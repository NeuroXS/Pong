#pragma once

#include "Racket.h"
#include "Ball.h"
#include "Score.h"

class Game
{
public:

	class Player
	{
	public:
		Racket racket;
		Score score;
	};

	static Game& get_instance();
	void start();

	// delete copy constructor and assignment operator
	Game(const Game&) = delete;
	Game& operator=(Game&) = delete;
private:
	Game();

	void handle_rackets();
	void handle_ball();
	void handle_win();
	void draw_game();

	RenderWindow window;


	Player left;
	Player right;
	Ball ball;
	RectangleShape net;
	
	Player* turn;
};

