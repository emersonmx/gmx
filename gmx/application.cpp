#include "gmx/application.hpp"

namespace gmx {

Application::Application()
    : running(true), errorCode(0) {}

Application::~Application() {}

int Application::run() {
    create();
    while (running) {
        update();
    }
    dispose();

    return errorCode;
}

void Application::exit(int errorCode) {
    running = false;
    this->errorCode = errorCode;
}

} /* namespace gmx */
