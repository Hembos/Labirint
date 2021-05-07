#include "Scene.h"

using namespace sf;

Scene::Scene(int cellSize, int labHeight, int labWeight)
{
	this->cellSize = cellSize;
	this->labHeight = labHeight;
	this->labWeight = labWeight;

	window = new RenderWindow(VideoMode(cellSize * labWeight + 120, cellSize * labHeight), "Labirint");
	window->setPosition(Vector2i(0, 0));

	mode = Mode::stop;

	labirint = new Labirint(labHeight, labWeight, cellSize);
	setStartBut = new Button("src/SetPosButton.png", Vector2i(cellSize * labWeight + 10, 0), Vector2i(31, 16));
	setEndBut = new Button("src/SetPosButtonEnd.png", Vector2i(cellSize * labWeight + 10, 33), Vector2i(31, 16));
	randomBut = new Button("src/Random.png", Vector2i(cellSize * labWeight + 10, 66), Vector2i(31, 16));
	drawBut = new Button("src/Draw.png", Vector2i(cellSize * labWeight + 10, 99), Vector2i(31, 16));
	eraseBut = new Button("src/Erase.png", Vector2i(cellSize * labWeight + 10, 132), Vector2i(31, 16));
	eraseOneBut = new Button("src/EraseOne.png", Vector2i(cellSize * labWeight + 10, 165), Vector2i(31, 16));
	newBut = new Button("src/New.png", Vector2i(cellSize * labWeight + 10, 198), Vector2i(31, 16));

	labirint->draw(*window);
	drawButtons();

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

			if (event.type == Event::MouseMoved && leftButPressed == true)
			{
				if (event.mouseMove.x < cellSize * labWeight && event.mouseMove.y < cellSize * labHeight && event.mouseMove.x >= 0 && event.mouseMove.y >= 0)
				{
					if (mode == Mode::createLabirint)
					{
						labirint->createLabirint(Vector2i(event.mouseMove.x, event.mouseMove.y));
					}
					if (mode == Mode::eraseLabirint)
					{
						labirint->erase(Vector2i(event.mouseMove.x, event.mouseMove.y));
					}
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
						drawButtons();

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
					if (eraseBut->isPressed(Vector2i(event.mouseButton.x, event.mouseButton.y)))
					{
						mode = Mode::stop;
						labirint->clear();

						window->clear();

						drawButtons();

						window->display();
					}
					if (eraseOneBut->isPressed(Vector2i(event.mouseButton.x, event.mouseButton.y)))
					{
						if (mode == Mode::eraseLabirint)
						{
							mode = Mode::stop;
						}
						else
						{
							mode = Mode::eraseLabirint;
						}
					}
					if (newBut->isPressed(Vector2i(event.mouseButton.x, event.mouseButton.y)))
					{
						window->close();
					}
				}
			}
		}
		
		if (mode == Mode::pathBuilding || mode == Mode::createLabirint || mode == Mode::eraseLabirint)
		{
			labirint->BFS();

			window->clear();

			labirint->draw(*window);
			labirint->drawPath(*window);

			drawButtons();

			window->display();

			if (mode == Mode::pathBuilding)
			{
				mode = Mode::stop;
			}
		}
	}
}

void Scene::drawButtons()
{
	setStartBut->draw(*window);
	setEndBut->draw(*window);
	randomBut->draw(*window);
	drawBut->draw(*window);
	eraseBut->draw(*window);
	eraseOneBut->draw(*window);
	newBut->draw(*window);
}