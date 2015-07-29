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

template <class T>
class TextureRegion {
    public:
        TextureRegion(Texture<T> texture) : texture(texture) {}
        virtual ~TextureRegion() {}

        inline int getX() { return texture.getWidth() * u; }
        inline void setX(int x) { u = x / texture.getWidth(); }
        inline int getY() { return texture.getHeight() * v; }
        inline void setY(int y) { v = y / texture.getHeight(); }
        inline int getWidth() { return texture.getWidth() * u2; }
        inline void setWidth(int width) { u2 = width / texture.getWidth(); }
        inline int getHeight() { return texture.getHeight() * v2; }
        inline void setHeight(int height) { v2 = height / texture.getHeight(); }
        void getRegion(int* x, int* y, int* width, int* height) {
            *x = getX();
            *y = getY();
            *width = getWidth();
            *height = getHeight();
        }
        void setRegion(int x, int y, int width, int height) {
            setX(x);
            setY(y);
            setWidth(width);
            setHeight(height);
        }

        inline float getU() { return u; }
        inline void setU(float u) { this->u = u; }
        inline float getV() { return v; }
        inline void setV(float v) { this->v = v; }
        inline float getU2() { return u2; }
        inline void setU2(float u2) { this->u2 = u2; }
        inline float getV2() { return v2; }
        inline void setV2(float v2) { this->v2 = v2; }
        inline void getRegion(float* u, float* v, float* u2, float* v2);
        inline void setRegion(float u, float v, float u2, float v2);

        inline const Texture<T> getTexture() { return texture; }

    private:
        float u;
        float v;
        float u2;
        float v2;
        Texture<T> texture;
};

}
#endif /* GMX_GAME_GRAPHICS_HPP */

