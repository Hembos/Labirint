#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <queue>

class Labirint
{
private:
	sf::Texture textureWall;
	sf::Sprite spriteWall;
	sf::Texture texturePath;
	sf::Sprite spritePath;
	std::vector<std::vector<int>> labirint;
	std::vector<std::vector<int>> visit;
	std::queue<sf::Vector2i> Queue;
	int height;
	int weight;
	int size;
public:
	Labirint(int height = 10, int weight = 10, int size = 20);
	void draw(sf::RenderWindow& window);
	void BFS();
	void print();
	void drawPath(sf::RenderWindow& window);
};