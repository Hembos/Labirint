#include "Labirint.h"
#include <ctime>
#include <iostream>

using namespace sf;

Labirint::Labirint(int height, int weight, int size)
	: height(height), weight(weight), size(size), startPos(Vector2i(-1, -1)), endPos(Vector2i(-1, -1))
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

	for (int i = 0; i < height; i++)
	{
		std::vector<int> tmp, tmp1;
		for (int j = 0; j < weight; j++)
		{
			tmp1.push_back(0);
			tmp.push_back(0);
			
		}
		visit.push_back(tmp1);
		labirint.push_back(tmp);
	}	
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
	if (startPos != Vector2i(-1, -1) && endPos != Vector2i(-1, -1))
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
	if (startPos != Vector2i(-1, -1) && endPos != Vector2i(-1, -1))
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
	}
	
	if (startPos != Vector2i(-1, -1))
	{
		spriteStart.setPosition(Vector2f(size * startPos.x, size * startPos.y));
		window.draw(spriteStart);
	}
	if (endPos != Vector2i(-1, -1))
	{
		spriteEnd.setPosition(Vector2f(size * endPos.x, size * endPos.y));
		window.draw(spriteEnd);
	}
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

void Labirint::createRandomLab()
{
	srand(time(0));

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < weight; j++)
		{
			int k = rand() % 100;
			if (k <= 20)
			{
				labirint[i][j] = 1;
			}
			else
			{
				labirint[i][j] = 0;
			}
		}
	}

	startPos = Vector2i(-1, -1);
	endPos = Vector2i(-1, -1);
}

void Labirint::createLabirint(Vector2i pos)
{
	pos.x /= size;
	pos.y /= size;

	labirint[pos.y][pos.x] = 1;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < weight; j++)
		{
			visit[i][j] = 0;
		}
	}
	
	if (startPos != Vector2i(-1, -1))
	{
		visit[startPos.y][startPos.x] = 1;
	}
}

void Labirint::clear()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < weight; j++)
		{
			visit[i][j] = 0;
			labirint[i][j] = 0;
		}
	}

	startPos = Vector2i(-1, -1);
	endPos = Vector2i(-1, -1);
}

void Labirint::erase(Vector2i pos)
{
	pos.x /= size;
	pos.y /= size;

	labirint[pos.y][pos.x] = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < weight; j++)
		{
			visit[i][j] = 0;
		}
	}

	if (startPos != Vector2i(-1, -1))
	{
		visit[startPos.y][startPos.x] = 1;
	}
}