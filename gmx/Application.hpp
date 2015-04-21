#ifndef GMX_APPLICATION_HPP
#define GMX_APPLICATION_HPP

namespace gmx {

class Application {
    public:
        Application() : running(true) {}
        virtual ~Application() {}

        void run();
        void exit();

    protected:
        virtual void create() = 0;
        virtual void dispose() = 0;
        virtual void update() = 0;

    private:
        bool running;
};

} /* namespace gmx */
#endif /* GMX_APPLICATION_HPP */

