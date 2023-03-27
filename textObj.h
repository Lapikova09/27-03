#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"
class Textobj {
private:
	sf::Text text;
	sf::Font font;
public:
	 Textobj(std::string str, sf::Vector2f position) {
		font.loadFromFile(FONT_FILENAME);
		text.setFont(font);
		text.setString(str);
		text.setCharacterSize(FONT_SIZE);
		text.setPosition(position);
	 }
	void update(std::string str) {
		text.setString(str);
	}
	void draw(sf::RenderWindow& window) {
		window.draw(text);
	}
};
