#include "gmx/Application.hpp"

namespace gmx {

void Application::run() {
    create();
    while (running) {
        update();
    }
    dispose();
}

void Application::exit() {
    running = false;
}

} /* namespace gmx */

