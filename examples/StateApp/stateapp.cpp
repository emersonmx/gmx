#include <cstdio>
#include <cstdlib>

#include "gmx/application.hpp"

using namespace std;

class StateApp : public gmx::StateApplication {
    protected:
        virtual void create() {
            printf("Created\n");
        }

        virtual void dispose() {
            printf("App disposed\n");
        }
};

class TestState : public gmx::DefaultState {
    public:
        TestState(StateApp& app) : app(app), count(1) {}
        virtual ~TestState() {}

        virtual void enter() {
            printf("State enter\n");
        }

        virtual void exit() {
            printf("State exit\n");
        }

        virtual void update() {
            printf("State updated %d\n", count);
            if (count++ >= 10) {
                app.exit();
            }
        }

        virtual void dispose() {
            printf("State disposed\n");
        }

    private:
        StateApp& app;
        int count;
};

int main() {
    StateApp app;
    app.setState(std::make_shared<TestState>(app));
    return app.run();
}
