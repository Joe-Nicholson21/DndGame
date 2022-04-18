#include <SDL.h>
#include "game.h"
#include "graphics.h"
#include "input.h"


namespace {
	const int FPS = 50;
	const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	this->gameLoop();
}

Game::~Game() {

}

void Game::gameLoop() {
	Graphics graphics;
	Input input;
	SDL_Event event;

	this->_player = AnimatedSprite(graphics, "D:/DungeonCrawlerApp/DnD game/sprites/icons.png", 0, 0, 30, 30, 100, 100, 300);
	this->_player.setupAnimations();
	this->_player.playAnimation("player");

	int LAST_UPDATE_TIME = SDL_GetTicks();

	while (true) {
		input.beginNewFrame();
		if (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN) {
				if (event.key.repeat == 0) {
					input.keyDownEvent(event);
				}
			}
			else if (event.type == SDL_KEYUP) {
				input.keyUpEvent(event);
			}
			else if (event.type == SDL_QUIT){
				return;
			}
		}
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE) == true) {
			return;
		}
		const int CURRENT_TIME = SDL_GetTicks();
		int ELAPSED_TIME = CURRENT_TIME - LAST_UPDATE_TIME;
		this->update(std::min(ELAPSED_TIME, MAX_FRAME_TIME));
		LAST_UPDATE_TIME = CURRENT_TIME;

		this->draw(graphics);
	}
}

void Game::draw(Graphics& graphics) {
	graphics.clear();
	this->_player.draw(graphics, 100, 100);

	graphics.flip();
}

void Game::update(float elapsedTime) {
	this->_player.update(elapsedTime);

}