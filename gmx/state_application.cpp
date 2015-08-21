#include "gmx/application.hpp"

namespace gmx {

StateApplication::StateApplication()
    : state(std::make_shared<DefaultState>()) {}

StateApplication::~StateApplication() {}

const StatePtr& StateApplication::getState() const {
    return state;
}

void StateApplication::setState(const StatePtr& state) {
    this->state->hide();
    this->state = state;
    this->state->show();
}

void StateApplication::update() {
    state->update();
}

}
