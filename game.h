#pragma once
#include "settings.h"
#include "meteor.h"
#include <vector>
#include "Player.h"

class Game {
public:
	enum GameState { PLAY, GAME_OVER };
	GameState gameState = PLAY;
	Game() {
	
		window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
		window.setFramerateLimit(FPS);
		meteorSprites.reserve(METEORS_QTY);
		for (int i = 0; i < METEORS_QTY; i++) {
			meteorSprites.push_back(new Meteor());
		}	
	}
	
	void play() {
		while (window.isOpen() && player.isAlife()) {
			checkEvents();
			update();
			if(player.getHp()<= 0) gameState = GAME_OVER;
			checkCollisions();
			draw();
		}
	}

private:
	sf::RenderWindow window;
	std::vector<Meteor*> meteorSprites;
	Player player;

	void checkEvents() {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	void update() {
		switch (gameState) {
		case PLAY:
			for (auto meteor : meteorSprites) {
				meteor->update();
			}
			player.update();
			break;
		case GAME_OVER:
			break;
		}
		
	}

	void checkCollisions() {
		sf::FloatRect playerBounds = player.getHitBox();
		for (auto& meteor : meteorSprites) {
			sf::FloatRect meteorBounds = meteor->getHitBox();
			if (meteorBounds.intersects(playerBounds)) {
				meteor->spawn();
				player.hpChange(meteor->GetDamage());
			}
		}
	}

	void draw() {
		switch (gameState) {
		case PLAY:
			window.clear();
			for (auto meteor : meteorSprites) {
				window.draw(meteor->getSprite());
			}
			player.draw(window);
			window.display();
			break;
		case GAME_OVER:
			window.clear();
			window.display();
			break;
		}
	}

};