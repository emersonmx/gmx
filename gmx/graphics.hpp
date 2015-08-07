#ifndef GMX_GAME_GRAPHICS_HPP
#define GMX_GAME_GRAPHICS_HPP

namespace gmx {

template <class T>
class Texture {
    public:
        Texture(T texture, int width, int height)
            : texture(texture), width(width), height(height) {}
        virtual ~Texture() {}

        T getData() { return texture; }
        int getWidth() { return width; }
        int getHeight() { return height; }
    protected:
        T texture;
        int width;
        int height;
};

template <class T>
class TextureRegion {
    public:
        TextureRegion(Texture<T>* texture) : texture(texture) {}
        virtual ~TextureRegion() {}

        int getX() { return texture->getWidth() * u; }
        void setX(int x) {
            u = (float) x / texture->getWidth();
        }
        int getY() { return texture->getHeight() * v; }
        void setY(int y) {
            v = (float) y / texture->getHeight();
        }
        int getWidth() { return texture->getWidth() * u2; }
        void setWidth(int width) {
            u2 = (float) width / texture->getWidth();
        }
        int getHeight() { return texture->getHeight() * v2; }
        void setHeight(int height) {
            v2 = (float) height / texture->getHeight();
        }
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

        float getU() { return u; }
        void setU(float u) { this->u = u; }
        float getV() { return v; }
        void setV(float v) { this->v = v; }
        float getU2() { return u2; }
        void setU2(float u2) { this->u2 = u2; }
        float getV2() { return v2; }
        void setV2(float v2) { this->v2 = v2; }
        void getRegion(float* u, float* v, float* u2, float* v2) {
            *u = getU();
            *v = getV();
            *u2 = getU2();
            *v2 = getV2();
        }
        void setRegion(float u, float v, float u2, float v2) {
            setU(u);
            setV(v);
            setU2(u2);
            setV2(v2);
        }

        Texture<T>* getTexture() { return texture; }

    protected:
        float u;
        float v;
        float u2;
        float v2;
        Texture<T>* texture;
};

}
#endif /* GMX_GAME_GRAPHICS_HPP */

