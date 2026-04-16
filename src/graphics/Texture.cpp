#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include <iostream>
#include <glad/glad.h>

#include "Texture.h"

Texture::Texture(const char* path)
{
    stbi_set_flip_vertically_on_load(true);
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    int w, h, channels;
    unsigned char* data = stbi_load(path, &w, &h, &channels, 0);

    if (!data)
    {
        std::cerr << "Failed to load texture: " << path << "\n";
        createDefault();
        return;
    }

    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format,
        w, h, 0, format, GL_UNSIGNED_BYTE, data);

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}

Texture::Texture()
{
    stbi_set_flip_vertically_on_load(true);
    createDefault();
}

void Texture::createDefault()
{
    const int size = 12;
    const int checkers = 6;
    unsigned char data[size * size * 4]; // RGBA

    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            int index = (y * size + x) * 4;

            int blockX = x * checkers / size;
            int blockY = y * checkers / size;
            bool altColor = (blockX + blockY) % 2 == 1;

            data[index + 0] = altColor ? 0 : 255; // R
            data[index + 1] = altColor ? 0 : 000; // G
            data[index + 2] = altColor ? 0 : 255; // B
            data[index + 3] = 255;                // A
        }
    }

    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        size,
        size,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        data
    );
}

void Texture::bind(unsigned int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, ID);
}

Texture::~Texture()
{
    glDeleteTextures(1, &ID);
}
