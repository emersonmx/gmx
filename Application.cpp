#include "gmx/Application.hpp"

namespace gmx {

void Application::exit() {
    running = false;
}

void Application::run() {
    create();
    while (running) {
        update();
    }
    dispose();
}

} /* namespace gmx */

