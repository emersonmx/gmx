#ifndef GMX_APPLICATION_HPP
#define GMX_APPLICATION_HPP

#include <memory>

namespace gmx {

class Application {
    public:
        Application();
        virtual ~Application();

        int run();
        void exit(int errorCode=0);

    protected:
        virtual void create() = 0;
        virtual void dispose() = 0;
        virtual void update() = 0;

    private:
        bool running;
        int errorCode;
};

class State {
    public:
        virtual ~State() {}

        virtual void enter() = 0;
        virtual void exit() = 0;
        virtual void update() = 0;
        virtual void dispose() = 0;
};

class DefaultState: public State {
    public:
        virtual ~DefaultState() {}

        virtual void enter() {}
        virtual void exit() {}
        virtual void update() {}
        virtual void dispose() {}
};

class StateApplication : public Application {
    public:
        StateApplication();
        virtual ~StateApplication();

        std::shared_ptr<State>& getState();
        void setState(const std::shared_ptr<State>& state);

        virtual void update();

    private:
        std::shared_ptr<State> state;
};

} /* namespace gmx */
#endif /* GMX_APPLICATION_HPP */
