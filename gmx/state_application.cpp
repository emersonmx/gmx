#include "gmx/application.hpp"

using namespace std;

namespace gmx {

StateApplication::StateApplication()
    : state(std::make_shared<DefaultState>()) {}

StateApplication::~StateApplication() {}

const shared_ptr<State>& StateApplication::getState() const {
    return state;
}

void StateApplication::setState(const shared_ptr<State>& state) {
    this->state->hide();
    this->state = state;
    this->state->show();
}

void StateApplication::update() {
    state->update();
}

}
