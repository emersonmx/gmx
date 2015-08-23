#ifndef GMX_GAME_GRAPHICS_HPP
#define GMX_GAME_GRAPHICS_HPP

#include <cmath>

namespace gmx {

template <class T>
class Texture {
    public:
        Texture(T texture, int width, int height)
            : texture(texture), width(width), height(height) {}
        virtual ~Texture() {}

        int getWidth() { return width; }
        int getHeight() { return height; }

        operator T() { return texture; }

    protected:
        T texture;
        int width;
        int height;
};

template <class T>
class TextureRegion {
    public:
        TextureRegion(Texture<T>* texture) : texture(texture) {
            setRegion(0, 0, texture->getWidth(), texture->getHeight());
        }
        TextureRegion(Texture<T>* texture, int width, int height) : texture(texture) {
            setRegion(0, 0, width, height);
        }
        TextureRegion(Texture<T>* texture, int x, int y, int width, int height)
                : texture(texture) {
            setRegion(x, y, width, height);
        }
        TextureRegion(Texture<T>* texture, float u, float v, float u2, float v2)
                : texture(texture) {
            setRegion(u, v, u2, v2);
        }
        virtual ~TextureRegion() {}

        void setRegion(int x, int y, int width, int height) {
            float invTexWidth = 1.f / texture->getWidth();
            float invTexHeight = 1.f / texture->getHeight();
            setRegion(x * invTexWidth, y * invTexHeight,
                      (x + width) * invTexWidth, (y + height) * invTexHeight);
            regionWidth = abs(width);
            regionHeight = abs(height);
        }
        void setRegion (float u, float v, float u2, float v2) {
            int texWidth = texture->getWidth(), texHeight = texture->getHeight();
            regionWidth = round(abs(u2 - u) * texWidth);
            regionHeight = round(abs(v2 - v) * texHeight);
            if (regionWidth == 1 && regionHeight == 1) {
                float adjustX = 0.25f / texWidth;
                u += adjustX;
                u2 -= adjustX;
                float adjustY = 0.25f / texHeight;
                v += adjustY;
                v2 -= adjustY;
            }

            this->u = u;
            this->v = v;
            this->u2 = u2;
            this->v2 = v2;
        }

        Texture<T>* getTexture() { return texture; }

        float getU() { return u; }
        void setU(float u) {
            this->u = u;
            regionWidth = round(abs(u2 - u) * texture->getWidth());
        }
        float getV() { return v; }
        void setV(float v) {
            this->v = v;
            regionHeight = round(abs(v2 - v) * texture->getHeight());
        }
        float getU2() { return u2; }
        void setU2() {
            this->u2 = u2;
            regionWidth = round(abs(u2 - u) * texture->getWidth());
        }
        float getV2 () { return v2; }
        void setV2 (float v2) {
            this->v2 = v2;
            regionHeight = round(abs(v2 - v) * texture->getHeight());
        }

        int getRegionX () { return round(u * texture->getWidth()); }
        void setRegionX (int x) { setU(x / (float) texture->getWidth()); }
        int getRegionY () { return round(v * texture->getHeight()); }
        void setRegionY (int y) { setV(y / (float) texture->getHeight()); }
        int getRegionWidth () { return regionWidth; }
        void setRegionWidth (int width) {
            if (isFlipX()) {
                setU(u2 + width / (float) texture->getWidth());
            } else {
                setU2(u + width / (float) texture->getWidth());
            }
        }
        int getRegionHeight () { return regionHeight; }
        void setRegionHeight (int height) {
            if (isFlipY()) {
                setV(v2 + height / (float) texture->getHeight());
            } else {
                setV2(v + height / (float) texture->getHeight());
            }
        }

        void flip (bool x, bool y) {
            if (x) {
                float temp = u;
                u = u2;
                u2 = temp;
            }
            if (y) {
                float temp = v;
                v = v2;
                v2 = temp;
            }
        }
        bool isFlipX () {
            return u > u2;
        }
        bool isFlipY () {
            return v > v2;
        }

    protected:
        float u;
        float v;
        float u2;
        float v2;
        int regionWidth, regionHeight;
        Texture<T>* texture;
};

}
#endif /* GMX_GAME_GRAPHICS_HPP */

