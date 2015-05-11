#include "gmx/application.hpp"

namespace gmx {

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