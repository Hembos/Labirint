#include "Labirint.h"
#include <ctime>
#include <iostream>

using namespace sf;

Labirint::Labirint(Vector2i startPos, Vector2i endPos, int height, int weight, int size)
	: height(height), weight(weight), size(size), startPos(startPos), endPos(endPos)
{
	textureWall.loadFromFile("src/Wall.png");
	spriteWall.setTexture(textureWall);
	spriteWall.setTextureRect(IntRect(0, 0, size, size));

	texturePath.loadFromFile("src/Path.png");
	spritePath.setTexture(texturePath);
	spritePath.setTextureRect(IntRect(0, 0, size, size));

	textureStart.loadFromFile("src/Start.png");
	spriteStart.setTexture(textureStart);
	spriteStart.setTextureRect(IntRect(0, 0, size, size));

	textureEnd.loadFromFile("src/End.png");
	spriteEnd.setTexture(textureEnd);
	spriteEnd.setTextureRect(IntRect(0, 0, size, size));

	srand(time(0));
	for (int i = 0; i < height; i++)
	{
		std::vector<int> tmp, tmp1;
		for (int j = 0; j < weight; j++)
		{
			tmp1.push_back(0);
			int k = rand() % 100;
			if (k <= 20)
			{
				tmp.push_back(1);
			}
			else
			{
				tmp.push_back(0);
			}
		}
		visit.push_back(tmp1);
		labirint.push_back(tmp);
	}
	if (labirint[startPos.y][startPos.x] == 1)
	{
		labirint[startPos.y][startPos.x] = 0;
	}
	visit[startPos.y][startPos.x] = 1;
	
}

void Labirint::draw(RenderWindow& window)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < weight; j++)
		{
			if (labirint[i][j] == 1)
			{
				spriteWall.setPosition(Vector2f(size * j, size * i));
				window.draw(spriteWall);
			}
			
		}
	}
}

void Labirint::BFS()
{
	Queue.push(startPos);

	while (!Queue.empty())
	{
		Vector2i currentPos = Queue.front();
		Queue.pop();

		int x = currentPos.x;
		int y = currentPos.y;

		if ((y + 1) < height && !visit[y + 1][x] && labirint[y + 1][x] == 0) 
		{
			visit[y + 1][x] = visit[y][x] + 1;
			Queue.push(Vector2i(x, y + 1));
		}
		if ((y - 1) >= 0 && !visit[y - 1][x] && labirint[y - 1][x] == 0) 
		{
			visit[y - 1][x] = visit[y][x] + 1;
			Queue.push(Vector2i(x, y - 1));
		}
		if ((x + 1) < weight && !visit[y][x + 1] && labirint[y][x + 1] == 0)
		{
			visit[y][x + 1] = visit[y][x] + 1;
			Queue.push(Vector2i(x + 1, y));
		}
		if ((x - 1) >= 0 && !visit[y][x - 1] && labirint[y][x - 1] == 0)
		{
			visit[y][x - 1] = visit[y][x] + 1;
			Queue.push(Vector2i(x - 1, y));
		}

	}
}

void Labirint::print()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < weight; j++)
		{
			std::cout << visit[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Labirint::drawPath(RenderWindow& window)
{
	int end = visit[endPos.y][endPos.x];
	int i = endPos.y;
	int j = endPos.x;
	if (end != 0)
	{
		while (end != 1)
		{
			spritePath.setPosition(Vector2f(size * j, size * i));
			window.draw(spritePath);
			if (i + 1 < height && visit[i + 1][j] != 0 && visit[i + 1][j] == end - 1)
			{
				i += 1;
				end -= 1;
				continue;
			}
			if (i - 1 >= 0 && visit[i - 1][j] != 0 && visit[i - 1][j] == end - 1)
			{
				i -= 1;
				end -= 1;
				continue;
			}
			if (j - 1 >= 0 && visit[i][j - 1] != 0 && visit[i][j - 1] == end - 1)
			{
				j -= 1;
				end -= 1;
				continue;
			}
			if (j + 1 >= 0 && visit[i][j + 1] != 0 && visit[i][j + 1] == end - 1)
			{
				j += 1;
				end -= 1;
				continue;
			}
		}
		spritePath.setPosition(Vector2f(size * startPos.x, size * startPos.y));
		window.draw(spritePath);
	}

	spriteStart.setPosition(Vector2f(size * startPos.x, size * startPos.y));
	window.draw(spriteStart);
	spriteEnd.setPosition(Vector2f(size * endPos.x, size * endPos.y));
	window.draw(spriteEnd);
}

void Labirint::setStartPos(sf::Vector2i startPos) 
{
	if (labirint[startPos.y][startPos.x] == 0)
	{
		this->startPos = startPos;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < weight; j++)
			{
				visit[i][j] = 0;
			}
		}

		visit[startPos.y][startPos.x] = 1;
	}
}

void Labirint::setEndPos(sf::Vector2i endPos)
{
	if (labirint[endPos.y][endPos.x] == 0)
	{
		this->endPos = endPos;
	}
}