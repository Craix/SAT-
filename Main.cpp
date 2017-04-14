#include <Windows.h>
#include "SFML\Graphics.hpp"
#include <iostream>
#include "mathematic.h"


sf::Vector2f lerp(sf::Vector2f from, sf::Vector2f to, float t = 1)
{
	// jeżeli pozycja początkowa i końcowa są takie same, to nie ma przesunięcia!
	if (from == to) return sf::Vector2f(0, 0);

	// policzenie wektora przesunięcia i jego długości
	sf::Vector2f offset = sf::Vector2f(to.x - from.x, to.y - from.y);
	float length = sqrtf(offset.x * offset.x + offset.y*offset.y);

	// normalizacja wektora
	offset = sf::Vector2f(offset.x / length, offset.y / length);

	offset.x *= t;
	offset.y *= t;

	return offset;
}

int main()
{
	sf::Vertex triangle[2];

	triangle[0].position = sf::Vector2f(50,100);
	triangle[1].position = sf::Vector2f(600, 80);

	sf::RectangleShape gracz, box;

	gracz.setSize(sf::Vector2f(50, 50));
	gracz.setOrigin(25, 25);
	gracz.setPosition(600, 400);
	gracz.setFillColor(sf::Color::Red);

	box.setSize(sf::Vector2f(100, 100));
	box.setOrigin(50, 50);
	box.setPosition(400, 300);
	box.setFillColor(sf::Color::Green);

	const float speed = 10.f;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Okno!");
	window.setFramerateLimit(60);

	sf::Clock zegar;
	sf::Time CzasOdAktualizacji = sf::Time::Zero;

	const sf::Time KrokCzasowy = sf::seconds(1.f / 60.f);

	srand(time(NULL));

	while (window.isOpen())
	{

		sf::Time Czas = zegar.restart();
		CzasOdAktualizacji += Czas;

		while (CzasOdAktualizacji > KrokCzasowy)
		{
			CzasOdAktualizacji -= KrokCzasowy;

			//event, game update etc...
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				gracz.move(sf::Vector2f(0, -1) * KrokCzasowy.asSeconds() * speed);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				gracz.move(sf::Vector2f(0, 1) * KrokCzasowy.asSeconds() * speed);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				gracz.move(sf::Vector2f(-1, 0) * KrokCzasowy.asSeconds() * speed);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				gracz.move(sf::Vector2f(1, 0) * KrokCzasowy.asSeconds() * speed);
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				gracz.move(lerp(gracz.getPosition(), (sf::Vector2f)sf::Mouse::getPosition(window), KrokCzasowy.asSeconds() * speed * 10));
			}

		}

		if (check(triangle, gracz))
		{
			gracz.setFillColor(sf::Color::Blue);
		}
		else
		{
			gracz.setFillColor(sf::Color::Red);
		}

		window.clear();

		window.draw(gracz);

		window.draw(triangle, 2, sf::Lines);

		window.draw(box);

		window.display();
	}
}



