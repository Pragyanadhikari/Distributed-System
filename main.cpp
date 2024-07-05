#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <vector>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int paddle_x = 300, paddle_y = 450;
int ball_x = 300, ball_y = 400;
int dx = -2, dy = -2;
int score = 0;
std::vector<std::vector<int>> bricks(5, std::vector<int>(10, 1));

void initialize()
{
    for (auto &row : bricks)
    {
        std::fill(row.begin(), row.end(), 1);
    }
}

void draw(sf::RenderWindow &window, sf::RectangleShape &paddle, sf::CircleShape &ball, sf::Font &font)
{
    window.clear();

    paddle.setPosition(paddle_x, paddle_y);
    window.draw(paddle);

    ball.setPosition(ball_x, ball_y);
    window.draw(ball);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (bricks[i][j] == 1)
            {
                sf::RectangleShape brick(sf::Vector2f(45, 15));
                brick.setFillColor(sf::Color::Red);
                brick.setPosition(j * 60 + 12, i * 20 + 12);
                window.draw(brick);
            }
        }
    }

    std::stringstream ss;
    ss << "Score: " << score;
    sf::Text text;
    text.setFont(font);
    text.setString(ss.str());
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    text.setPosition(5, 0);
    window.draw(text);

    window.display();
}

void input(sf::RenderWindow &window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        paddle_x -= 20;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        paddle_x += 20;
    }

    if (paddle_x <= 0)
    {
        paddle_x = 0;
    }
    if (paddle_x >= 500)
    {
        paddle_x = 500;
    }
}

void move()
{
    ball_x += dx;
    ball_y += dy;

    if (ball_x >= paddle_x && ball_x <= paddle_x + 100 && ball_y >= paddle_y - 10 && ball_y <= paddle_y + 10)
    {
        dy = -dy;
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (bricks[i][j] == 1)
            {
                if (ball_x >= j * 60 + 10 && ball_x <= j * 60 + 60 && ball_y >= i * 20 + 10 && ball_y <= i * 20 + 30)
                {
                    bricks[i][j] = 0;
                    dy = -dy;
                    score++;
                }
            }
        }
    }

    if (ball_x <= 0 || ball_x >= 590)
    {
        dx = -dx;
    }

    if (ball_y <= 0)
    {
        dy = -dy;
    }

    if (ball_y >= 490)
    {
        std::cout << "Game Over" << std::endl;
        std::cout << "Press any key to exit" << std::endl;
        exit(0);
    }
    if (score == 50)
    {
        std::cout << "Congratulations! You won the game." << std::endl;
        exit(0);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 500), "Brick Breaker Game");
    window.setFramerateLimit(60);

    sf::RectangleShape paddle(sf::Vector2f(100, 10));
    paddle.setFillColor(sf::Color::White);

    sf::CircleShape ball(10);
    ball.setFillColor(sf::Color::Yellow);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "Could not load font" << std::endl;
        return -1;
    }

    initialize();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        input(window);
        move();
        draw(window, paddle, ball, font);

        sf::sleep(sf::milliseconds(10));
    }

    return 0;
}

/*
#include <SFML/Graphics.hpp>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <time.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int paddle_x = 300, paddle_y = 450;
int ball_x = 300, ball_y = 400;
int dx = -2, dy = -2;
int score = 0;
int bricks[5][10];
char buf[10];

void initialize()
{
    int i, j;

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 10; j++)
        {
            bricks[i][j] = 1;
        }
    }
}

void draw()
{
    int i, j;

    cleardevice();
    setfillstyle(SOLID_FILL, WHITE);
    bar(paddle_x, paddle_y, paddle_x + 100, paddle_y + 10);
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse(ball_x, ball_y, 10, 10);

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (bricks[i][j] == 1)
            {
                setfillstyle(SOLID_FILL, RED);
                bar(j * 60 + 12, i * 20 + 12, j * 60 + 57, i * 20 + 27);
            }
        }
    }

    outtextxy(5, 0, "Score: ");
}

void input()
{
    if (kbhit())
    {
        switch (getch())
        {
        case LEFT:
            paddle_x -= 20;
            break;
        case RIGHT:
            paddle_x += 20;
            break;
        }
    }

    if (paddle_x <= 0)
    {
        paddle_x = 0;
    }
    if (paddle_x >= 500)
    {
        paddle_x = 500;
    }
}

void move()
{
    int i, j;

    ball_x += dx;
    ball_y += dy;

    if (ball_x >= paddle_x && ball_x <= paddle_x + 100 && ball_y >= paddle_y - 10 && ball_y <= paddle_y + 10)
    {
        dy = -dy;
    }

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 10; j++)
        {
            if (bricks[i][j] == 1)
            {
                if (ball_x >= j * 60 + 10 && ball_x <= j * 60 + 60 && ball_y >= i * 20 + 10 && ball_y <= i * 20 + 30)
                {
                    bricks[i][j] = 0;
                    dy = -dy;
                    score++;
                }
            }
        }
    }

    if (ball_x <= 0 || ball_x >= 590)
    {
        dx = -dx;
    }

    if (ball_y <= 0)
    {
        dy = -dy;
    }

    if (ball_y >= 490)
    {
        outtextxy(200, 200, "Game Over");
        outtextxy(200, 230, "Press any key to exit");
        getch();
        exit(0);
    }
    if (score == 50)
    {
        draw();
        outtextxy(200, 200, "Congratulations! You won the game.");
        getch();
        exit(0);
    }
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    initialize();
    draw();

    while (1)
    {
        move();
        input();
        draw();
        delay(10);
    }

    getch();
    closegraph();
    return 0;
}*/