#ifndef GMX_GAME_HPP
#define GMX_GAME_HPP

#include <memory>

#include "gmx/Application.hpp"
#include "gmx/DefaultScreen.hpp"

namespace gmx {

class Game : public Application {
    public:
        typedef std::shared_ptr<Screen> ScreenPtr;

        Game();
        virtual ~Game() {}

        inline const ScreenPtr& getScreen() const { return screen; }
        void setScreen(const ScreenPtr& screen);

        virtual void update();

    private:
        ScreenPtr screen;
};

} /* namespace gmx */
#endif /* GMX_GAME_HPP */

