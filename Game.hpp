#ifndef GMX_GAME_HPP
#define GMX_GAME_HPP

#include "gmx/Application.hpp"
#include "gmx/DefaultScreen.hpp"

namespace gmx {

class Game : public Application {
    public:
        Game() : screen(NULL) {}
        Screen* getScreen() const { return screen; }
        void setScreen(Screen* screen) {
            if (this->screen != NULL) {
                this->screen->hide();
            }
            screen->show();
            this->screen = screen;
        }

        virtual void update() {
            screen->update();
        }

    private:
        Screen* screen;
};

} /* namespace gmx */
#endif /* GMX_GAME_HPP */

