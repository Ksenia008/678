#include <SFML/Graphics.hpp>
#include "settings.h"
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
	window.setFramerateLimit(FPS);

	//Создание объектов
	RectangleShape leftBat, rightBat;
	leftBat.setSize(BAT_SIZE);
	leftBat.setFillColor(LEFT_BAT_COLOR);
	leftBat.setPosition(BAT_OFFSET, (WINDOW_HEIGHT - BAT_SIZE.y) / 2);
	rightBat.setSize(BAT_SIZE);
	rightBat.setFillColor(RIGHT_BAT_COLOR);
	rightBat.setPosition(WINDOW_WIDTH - BAT_OFFSET - BAT_SIZE.x, (WINDOW_HEIGHT - BAT_SIZE.y) / 2);

	CircleShape ball(BALL_RADIUS);
	ball.setFillColor(BALL_COLOR);
	ball.setPosition((WINDOW_WIDTH - 2 * BALL_RADIUS) / 2,
		(WINDOW_HEIGHT - 2 * BALL_RADIUS) / 2);

	float ballSpeedX = 2.f;
	float ballSpeedY = 3.f;
	
	//шрифт
	Font font;
	font.loadFromFile("DS-DIGIB.ttf");
	//переменные для счета
	int LeftScore = 0;
	int RightScore = 0;
	//Тексты для отображения на экране
	Text leftText;
	leftText.setString(std::to_string(LeftScore));
	leftText.setFont(font);
	leftText.setCharacterSize(FONT_SIZE);
	leftText.setPosition(LEFT_TEXT_POS);
	Text rightText;
	rightText.setString(std::to_string(RightScore));
	rightText.setFont(font);
	rightText.setCharacterSize(FONT_SIZE);
	rightText.setPosition(RIGHT_NEXT_POS);


	while (window.isOpen())
	{
		//1 обработка событий
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		//Обновление игровых объектов
		ball.move(ballSpeedX, ballSpeedY);
		//мяч отскакивает от левой или от правой границ экрана
		//от левой
		if (ball.getPosition().x <= 0) 
		{
			ballSpeedX = -ballSpeedX;
			RightScore++;
			rightText.setString(std::to_string(RightScore));
		}
		//от правой
		if	(ball.getPosition().x + 2 * BALL_RADIUS >= WINDOW_WIDTH)
		{
			ballSpeedX = -ballSpeedX;
			LeftScore++;
			leftText.setString(std::to_string(LeftScore));
		}
		//ЛЕВАЯ РАКЕТКА
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			leftBat.move(0.f, -BAT_DY);
		}
		else if (Keyboard::isKeyPressed(Keyboard::S)) {
			leftBat.move(0.f, BAT_DY);
		}
		//Правая ракетка
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			rightBat.move(0.f, -BAT_DY);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down)) {
			rightBat.move(0.f, BAT_DY);
		}
		//отрисовка объектов и обновление окна
		window.clear();
		window.draw(leftBat);
		window.draw(rightBat);
		window.draw(ball);
		
		window.draw(leftText);
		window.draw(rightText);
		window.display();
	}

	return 0;
}