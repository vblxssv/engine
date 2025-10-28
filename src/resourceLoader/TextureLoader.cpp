#include "TextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../external/stb_image/stb_image.h"

std::shared_ptr<Texture> TextureLoader::load(const std::string& path)
{
    int width, height, channels;

    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Error: Failed to load texture from " << path << std::endl;
        return nullptr;
    }

    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    return std::make_shared<Texture>(id, width, height, channels);
}

