#include <cstdio>
#include <cstdlib>

#include <GLFW/glfw3.h>

#include "gmx/application.hpp"
#include "gmx/graphics.hpp"
#include "gmx/loaders.hpp"

using namespace std;

#define WINDOW_TITLE "TextureApp"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

class TextureApp : public gmx::Application {
    public:
        TextureApp() : Application(), window(NULL) {}
        virtual ~TextureApp() {}

    protected:
        virtual void create() {
            if(!glfwInit()) {
                exit(-1);
                return;
            }

            window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
            if (window == NULL) {
                exit(-1);
                return;
            }

            glfwMakeContextCurrent(window);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, 1, -1);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glEnable(GL_TEXTURE_2D);

            glClearColor(0, 0, 0, 1);

            texture = gmx::loadTexture("hello.png");
        }

        virtual void dispose() {
            delete texture;

            glfwDestroyWindow(window);
            glfwTerminate();
        }

        virtual void update() {
            glfwPollEvents();

            if (glfwWindowShouldClose(window)) {
                exit();
            }

            glClear(GL_COLOR_BUFFER_BIT);

            glBegin(GL_QUADS);
                glTexCoord2f(0.0f, 0.0f);
                glVertex2f(0, 0);

                glTexCoord2f(1.0f, 0.0f);
                glVertex2f(texture->getWidth(), 0);

                glTexCoord2f(1.0f, 1.0f);
                glVertex2f(texture->getWidth(), texture->getHeight());

                glTexCoord2f(0.0f, 1.0f);
                glVertex2f(0, texture->getHeight());
            glEnd();

            glfwSwapBuffers(window);
        }

    private:
        GLFWwindow* window;
        gmx::Texture* texture;
};

int main(int argc, char* argv[]) {
    TextureApp app;
    return app.run();
}
