#ifndef GMX_DEFAULT_SCREEN_HPP
#define GMX_DEFAULT_SCREEN_HPP

#include <iostream>

#include "gmx/screen.hpp"

namespace gmx {

class DefaultScreen: public Screen {
    public:
        virtual ~DefaultScreen() {}

        virtual void show() {}
        virtual void hide() {}
        virtual void update() {}
        virtual void dispose() {}
};

} /* namespace gmx */
#endif /* GMX_DEFAULT_SCREEN_HPP */
