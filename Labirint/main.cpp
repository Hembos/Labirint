#include <iostream>
#include "Labirint.h"

using namespace sf;

int main()
{
	const int size = 30;
	const int height = 20;
	const int weight = 20;

	Labirint labirint(height, weight, size);
	labirint.BFS();
	labirint.print();
	
	RenderWindow* window = new RenderWindow(VideoMode(size * weight, size * height), "Labirint");
	window->setPosition(Vector2i(300, 100));

	while (window->isOpen())
	{
		Event event;

		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			
		}

		window->clear();

		labirint.draw(*window);
		labirint.drawPath(*window);

		window->display();
	}
	return 0;
}