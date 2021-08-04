#include "game.h"

bool Game::running = true;

void Game::Stop() {
	Game::running = false;
}
