#include "Game.h"
#include "CONSTANTS.h"

using namespace sf;

Game& Game::get_instance()
{
	static Game game{};
	return game;
}

Game::Game() :
    window{ VideoMode({(int) WIDTH, (int) HEIGHT}), "Pong" },
    left{},
    right{},
    net({ 1.f, HEIGHT - (2.f * 6.f / 100.f * HEIGHT) }),
    ball{},
    turn{&right}
{
    // Frame limit
    window.setFramerateLimit(60);

    // Rackets
    left.racket.setPosition({ SPACE_BEHIND_RACKET, (HEIGHT / 2) - (RACKET_HEIGHT/2) });
    right.racket.setPosition({ WIDTH - (SPACE_BEHIND_RACKET) - RACKET_WIDTH, (HEIGHT / 2) - (RACKET_HEIGHT / 2) });

    // Scores
    left.score.setPosition({ (WIDTH / 4) , 0 });
    right.score.setPosition({ (WIDTH - (WIDTH/4)), 0});

    // net
    net.setPosition({ WIDTH / 2, 6.f / 100.f * HEIGHT });



}

void Game::start()
{
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }


        handle_ball();
        handle_rackets();

        draw_game();
    }
}

void Game::draw_game()
{
    ball.moveBall();

    window.clear();

    window.draw(left.score);
    window.draw(left.racket);

    window.draw(net);
    window.draw(ball);



    window.draw(right.racket);
    window.draw(right.score);

    window.display();
}

void Game::handle_rackets()
{
    static float BOTTOM = HEIGHT - RACKET_HEIGHT;
    if (Keyboard::isKeyPressed(Keyboard::Key::Up))
    {
        if(right.racket.getPosition().y >= 0)
            right.racket.move({ 0.f,-RACKET_STEPS });
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::Down))
    {
        if (right.racket.getPosition().y <= BOTTOM)
            right.racket.move({ 0.f,RACKET_STEPS });
    }

    if (Keyboard::isKeyPressed(Keyboard::Key::W))
    {
        if (left.racket.getPosition().y >= 0)
            left.racket.move({ 0.f,-RACKET_STEPS });
    }
    else if (Keyboard::isKeyPressed(Keyboard::Key::S))
    {
        if (left.racket.getPosition().y <= BOTTOM)
            left.racket.move({ 0.f,RACKET_STEPS });
    }
}

void Game::handle_ball()
{
    const static float BOTTOM = HEIGHT - (2.f * RADIUS);
    const static float LEFT = left.racket.getPosition().x + RACKET_WIDTH;
    const static float DIAMETER = 2 * RADIUS;
    const static float RIGHT = right.racket.getPosition().x - DIAMETER;
    const static float MID_RACKET = RACKET_HEIGHT / 2.f;
    const static float SQRT2 = sqrt(2);

    Vector2f ballPos = ball.getGlobalBounds().position;

    
    if (ballPos.x <= LEFT || ballPos.x >= RIGHT) // rackets collisions
    {
        const float racketY = turn->racket.getPosition().y;
        const float midOfRacket = racketY + MID_RACKET;
        const float endOfBallY = ballPos.y + DIAMETER;

        if (midOfRacket >= ballPos.y && midOfRacket <= endOfBallY)
        {
            if (ball.velocity.y == 0.f)
            {
                ball.velocity = { - ball.velocity.x, 0.f };
            }
            else
            {
            ball.velocity = { - SQRT2 * ball.velocity.x, 0.f};
            }
        }
        else if (endOfBallY >= racketY && ballPos.y <= racketY + RACKET_HEIGHT)
        {
            if (ball.velocity.y == 0.f)
            {
                if (ballPos.y > midOfRacket)
                {
                    ball.velocity = { -ball.velocity.x / SQRT2, BALL_VELOCITY };
                }
                else
                {
                    ball.velocity = { -ball.velocity.x / SQRT2, -BALL_VELOCITY };
                }
            }
            else
            {
                ball.velocity = { -ball.velocity.x, ball.velocity.y };
            }
        }
        else
        {
            handle_win();
        }

        if (turn == &left)
            turn = &right;
        else
            turn = &left;

    }
    else if (ballPos.y <= 0 || ballPos.y >= BOTTOM) // horizontal surfaces
    {
        // top or bottom
        ball.velocity = { ball.velocity.x, -ball.velocity.y };
    }
}

void Game::handle_win()
{
    static const float DIAMETER = 2.f * RADIUS;

    if (turn == &left)
    {

        while (ball.getPosition().x + DIAMETER > 0)
        {
            handle_rackets();

            draw_game();
        }

        right.score++;

        ball.velocity = { -BALL_VELOCITY, BALL_VELOCITY };

        turn = &right; // gonna be switched later in handle_ball
    }
    else
    {
        while (ball.getPosition().x < WIDTH)
        {
            handle_rackets();

            draw_game();
        }

        left.score++;

        ball.velocity = { BALL_VELOCITY, BALL_VELOCITY};

        turn = &left; // gonna be switched later in handle_ball
    }

    // reset
    ball.reset();


    left.racket.setPosition({ SPACE_BEHIND_RACKET, (HEIGHT / 2) - (RACKET_HEIGHT / 2) });
    right.racket.setPosition({ WIDTH - (SPACE_BEHIND_RACKET)-RACKET_WIDTH, (HEIGHT / 2) - (RACKET_HEIGHT / 2) });

    sf::sleep(seconds(2));
}