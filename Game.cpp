#include "Game.hpp"

namespace gmx {

Game::Game() : screen(std::make_shared<DefaultScreen>()) {}

void Game::setScreen(const ScreenPtr& screen) {
    this->screen->hide();
    screen->show();
    this->screen = screen;
}

void Game::update() {
    screen->update();
}

}
