#ifndef GMX_APPLICATION_HPP
#define GMX_APPLICATION_HPP

namespace gmx {

class Application {
    public:
        Application() : running(true), errorCode(0) {}
        virtual ~Application() {}
        
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

} /* namespace gmx */
#endif /* GMX_APPLICATION_HPP */