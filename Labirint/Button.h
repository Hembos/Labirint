#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button
{
	using Vector = sf::Vector2i;
private:
	sf::Texture texture;
	sf::Sprite sprite;
	Vector pos;
	Vector size;
public:
	Button(std::string textureFile, Vector pos, Vector size)
		: pos(pos)
	{
		texture.loadFromFile(textureFile);
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
		sprite.setPosition((sf::Vector2f)pos);
		sprite.scale(2, 2);
		this->size = Vector(size.x * 2, size.y * 2);
	}
	void draw(sf::RenderWindow& window) { window.draw(sprite); }
	bool isPressed(Vector mousePos)
	{
		if (mousePos.x >= pos.x && mousePos.x <= pos.x + size.x && mousePos.y >= pos.y && mousePos.y <= pos.y + size.y)
		{
			return true;
		}
		return false;
	}
};