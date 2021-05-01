#pragma once
#include "Labirint.h"
#include "Button.h"

enum class Mode
{
	placementPosStart,
	placementPosEnd,
	pathBuilding,
	createLabirint,
	stop
};

class Scene
{
private:
	sf::RenderWindow* window;
	Labirint* labirint;
	Mode mode;
	int cellSize;
	int labHeight;
	int labWeight;
	Button* setStartBut;
	Button* setEndBut;
	Button* randomBut;
	Button* drawBut;
public:
	Scene();
	void start();
};