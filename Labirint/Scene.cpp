#include "Scene.h"

using namespace sf;

Scene::Scene()
{
	cellSize = 10;
	const int height = 50;
	const int weight = 50;
	const Vector2i startPos = Vector2i(1, 1);
	const Vector2i endPos = Vector2i(8, 10);

	window = new RenderWindow(VideoMode(cellSize * weight, cellSize * height), "Labirint");
	window->setPosition(Vector2i(0, 0));

	mode = Mode::pathBuilding;

	labirint = new Labirint(startPos, endPos, height, weight, cellSize);
}

void Scene::start()
{
	while (window->isOpen())
	{
		Event event;

		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();
		}
		
		if (event.type == Event::MouseButtonPressed)
		{
			if (mode == Mode::placementPos)
			{

			}
			if (event.mouseButton.button == Mouse::Left)
			{
				Vector2i startPos = Vector2i(event.mouseButton.x / cellSize, event.mouseButton.y / cellSize);
				labirint->setStartPos(startPos);
				mode = Mode::pathBuilding;
			}
			if (event.mouseButton.button == Mouse::Right)
			{
				Vector2i endPos = Vector2i(event.mouseButton.x / cellSize, event.mouseButton.y / cellSize);
				labirint->setEndPos(endPos);
				mode = Mode::pathBuilding;
			}
		}

		if (mode != Mode::stop)
		{
			labirint->BFS();

			window->clear();

			labirint->draw(*window);
			labirint->drawPath(*window);

			window->display();
		}

		mode = Mode::stop;
	}
}