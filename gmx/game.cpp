#include "gmx/game.hpp"

namespace gmx {

Game::Game()
    : screen(std::make_shared<DefaultScreen>()) {}

Game::~Game() {}

const Game::ScreenPtr& Game::getScreen() const {
    return screen;
}

void Game::setScreen(const Game::ScreenPtr& screen) {
    this->screen->hide();
    screen->show();
    this->screen = screen;
}

void Game::update() {
    screen->update();
}

}
