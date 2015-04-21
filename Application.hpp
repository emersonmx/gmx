#ifndef GMX_APPLICATION_HPP
#define GMX_APPLICATION_HPP

#include <cstdlib>

namespace gmx {

class Application {
    public:
        Application() : running(true) {}
        virtual ~Application() {}

        void exit();

        virtual void create() = 0;

        virtual void dispose() = 0;

        virtual void update() = 0;

        void run();

    private:
        bool running;
};

} /* namespace gmx */
#endif /* GMX_APPLICATION_HPP */

