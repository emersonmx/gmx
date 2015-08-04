#ifndef GMX_GAME_HPP
#define GMX_GAME_HPP

#include <memory>

#include "gmx/application.hpp"
#include "gmx/screen.hpp"

namespace gmx {

class Game : public Application {
    public:
        typedef std::shared_ptr<Screen> ScreenPtr;

        Game();
        virtual ~Game();

        const ScreenPtr& getScreen() const;
        void setScreen(const ScreenPtr& screen);

        virtual void update();

    private:
        ScreenPtr screen;
};

} /* namespace gmx */
#endif /* GMX_GAME_HPP */
