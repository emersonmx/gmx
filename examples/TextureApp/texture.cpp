#include <cstdio>
#include <cstdlib>

#include <GLFW/glfw3.h>
#include <FreeImage.h>

#include "gmx/application.hpp"
#include "gmx/graphics.hpp"

using namespace std;

#define WINDOW_TITLE "TextureApp"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

class Texture : public gmx::Texture {
    public:
        Texture(GLuint textureId, int width, int height)
            : textureId(textureId), gmx::Texture(width, height) {}

        inline GLuint getTexture() { return textureId; }

    protected:
        GLuint textureId;
};

static FIBITMAP* loadImage(const char* filename) {
    FREE_IMAGE_FORMAT fif = FreeImage_GetFIFFromFilename(filename);
    return FreeImage_Load(fif, filename, 0);
}

static GLuint createTexture(int width, int height, void* data) {
    GLuint textureId = 0;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height,
        0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    return textureId;
}

Texture* loadTexture(const char* filename) {
    GLuint textureId = 0;
    int width, height;

    FIBITMAP* dib = loadImage(filename);
    if (dib == NULL) {
        fprintf(stderr, "Não foi possível carregar a image \"%s\"\n", filename);
        return NULL;
    }

    FIBITMAP* image = FreeImage_ConvertTo32Bits(dib);
    FreeImage_Unload(dib);
    if (image == NULL) {
        fprintf(stderr, "Não foi possível converter a image \"%s\"\n", filename);
        return NULL;
    }

    width = FreeImage_GetWidth(image);
    height = FreeImage_GetHeight(image);

    void* data = FreeImage_GetBits(image);
    textureId = createTexture(width, height, data);
    if (textureId == 0) {
        fprintf(stderr, "Não criar a textura da imagem \"%s\"\n", filename);
    }
    FreeImage_Unload(image);

    return new Texture(textureId, width, height);
}

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

            texture = loadTexture("assets/hello.png");
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

            glLoadIdentity();

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
        Texture* texture;
};

int main(int argc, char* argv[]) {
    TextureApp app;
    return app.run();
}
