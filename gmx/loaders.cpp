#include "gmx/loaders.hpp"

#include <cstdio>

#include <FreeImage.h>

#include "gmx/graphics.hpp"

namespace gmx {

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

} /* namespace gmx */
