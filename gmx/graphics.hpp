#ifndef GMX_GAME_GRAPHICS_HPP
#define GMX_GAME_GRAPHICS_HPP

namespace gmx {

template <class T>
class Texture {
    public:
        Texture(T texture, int width, int height)
            : texture(texture), width(width), height(height) {}
        virtual ~Texture() {}

        inline T getTexture() { return texture; }
        inline int getWidth() { return width; }
        inline int getHeight() { return height; }

    protected:
        T texture;
        int width;
        int height;
};

}
#endif /* GMX_GAME_GRAPHICS_HPP */

