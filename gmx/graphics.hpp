#ifndef GMX_GAME_GRAPHICS_HPP
#define GMX_GAME_GRAPHICS_HPP

#include <GLFW/glfw3.h>

namespace gmx {

class Texture {
    public:
        Texture(GLuint id, int width, int height) : id(id), width(width),
            height(height) {}

        inline GLuint getId() { return id; }
        inline int getWidth() { return width; }
        inline int getHeight() { return height; }

    private:
        GLuint id;
        int width;
        int height;
};

}
#endif /* GMX_GAME_GRAPHICS_HPP */

