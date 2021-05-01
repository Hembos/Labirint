#include "Scene.h"

using namespace sf;

Scene::Scene()
{
	cellSize = 20;
	labHeight = 20;
	labWeight = 20;

	window = new RenderWindow(VideoMode(cellSize * labWeight + 120, cellSize * labHeight), "Labirint");
	window->setPosition(Vector2i(0, 0));

	mode = Mode::stop;

	labirint = new Labirint(labHeight, labWeight, cellSize);
	setStartBut = new Button("src/SetPosButton.png", Vector2i(cellSize * labWeight + 10, 0), Vector2i(31, 16));
	setEndBut = new Button("src/SetPosButtonEnd.png", Vector2i(cellSize * labWeight + 10, 50), Vector2i(31, 16));
	randomBut = new Button("src/Random.png", Vector2i(cellSize * labWeight + 10, 100), Vector2i(31, 16));
	drawBut = new Button("src/Draw.png", Vector2i(cellSize * labWeight + 10, 150), Vector2i(31, 16));

	labirint->draw(*window);
	setStartBut->draw(*window);
	setEndBut->draw(*window);
	randomBut->draw(*window);
	drawBut->draw(*window);

	window->display();
}

void Scene::start()
{
	bool leftButPressed = false;

	while (window->isOpen())
	{
		Event event;

		while (window->pollEvent(event))
		{
			if (event.type == Event::Closed)
				window->close();

			if (event.type == Event::MouseMoved && leftButPressed == true && mode == Mode::createLabirint)
			{
				if (event.mouseMove.x < cellSize * labWeight && event.mouseMove.y < cellSize * labHeight && event.mouseMove.x >= 0 && event.mouseMove.y >= 0)
				{
					labirint->createLabirint(Vector2i(event.mouseMove.x, event.mouseMove.y), *window);
				}
			}

			if (event.type == Event::MouseButtonReleased)
			{
				leftButPressed = false;
			}

			if (event.type == Event::MouseButtonPressed)
			{
				leftButPressed = true;
				if (mode == Mode::placementPosStart)
				{
					if (event.mouseButton.button == Mouse::Left && event.mouseButton.x < cellSize * labWeight)
					{
						Vector2i startPos = Vector2i(event.mouseButton.x / cellSize, event.mouseButton.y / cellSize);
						labirint->setStartPos(startPos);
						mode = Mode::pathBuilding;
						labirint->BFS();
					}
				}
				if (mode == Mode::placementPosEnd)
				{
					if (event.mouseButton.button == Mouse::Left && event.mouseButton.x < cellSize * labWeight)
					{
						Vector2i endPos = Vector2i(event.mouseButton.x / cellSize, event.mouseButton.y / cellSize);
						labirint->setEndPos(endPos);
						mode = Mode::pathBuilding;
					}
				}
				if (mode == Mode::createLabirint)
				{
					if (event.mouseButton.button == Mouse::Left && event.mouseButton.x < cellSize * labWeight)
					{
						labirint->createLabirint(Vector2i(event.mouseButton.x, event.mouseButton.y), *window);
					}
				}

				if (event.mouseButton.button == Mouse::Left)
				{
					if (setStartBut->isPressed(Vector2i(event.mouseButton.x, event.mouseButton.y)))
					{
						mode = Mode::placementPosStart;
					}
					if (setEndBut->isPressed(Vector2i(event.mouseButton.x, event.mouseButton.y)))
					{
						mode = Mode::placementPosEnd;
					}
					if (randomBut->isPressed(Vector2i(event.mouseButton.x, event.mouseButton.y)))
					{
						labirint->createRandomLab();

						window->clear();

						labirint->draw(*window);
						setStartBut->draw(*window);
						setEndBut->draw(*window);
						randomBut->draw(*window);
						drawBut->draw(*window);

						window->display();
					}
					if (drawBut->isPressed(Vector2i(event.mouseButton.x, event.mouseButton.y)))
					{
						if (mode == Mode::createLabirint)
						{
							mode = Mode::stop;
						}
						else
						{
							mode = Mode::createLabirint;
						}
					}
				}
			}
		}
		
		if (mode == Mode::pathBuilding || mode == Mode::createLabirint)
		{
			labirint->BFS();

			window->clear();

			labirint->draw(*window);
			labirint->drawPath(*window);

			setStartBut->draw(*window);
			setEndBut->draw(*window);
			randomBut->draw(*window);
			drawBut->draw(*window);

			window->display();

			if (mode == Mode::pathBuilding)
			{
				mode = Mode::stop;
			}
		}
	}
}