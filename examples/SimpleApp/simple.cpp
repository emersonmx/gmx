#include <cstdio>
#include <cstdlib>

#include "gmx/application.hpp"

using namespace std;

class SimpleApp : public gmx::Application {
    public:
        SimpleApp() : Application(), count(1) {}
        virtual ~SimpleApp() {}

    protected:
        virtual void create() {
            printf("Created\n");
        }

        virtual void dispose() {
            printf("Disposed\n");
        }

        virtual void render() {
            printf("render %d\n", count);
            if (count++ >= 10) {
                exit();
            }
        }

    private:
        int count;
};

int main(int argc, char* argv[]) {
    SimpleApp app;
    return app.run();
}
