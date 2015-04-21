#ifndef GMX_SCREEN_HPP
#define GMX_SCREEN_HPP

namespace gmx {

class Screen {
    public:
        virtual ~Screen() {}

        virtual void show() = 0;
        virtual void hide() = 0;
        virtual void update() = 0;
        virtual void dispose() = 0;
};

} /* namespace gmx */
#endif /* GMX_SCREEN_HPP */

