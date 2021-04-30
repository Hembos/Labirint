#pragma once
#include "Labirint.h"

enum class Mode
{
	placementPos,
	pathBuilding,
	stop
};

class Scene
{
private:
	sf::RenderWindow* window;
	Labirint* labirint;
	Mode mode;
	int cellSize;
public:
	Scene();
	void start();
};