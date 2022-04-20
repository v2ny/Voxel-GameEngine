#include <Texture.h>

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
    type = texType;
    int widthImg, heightImg, numColCh{};
    unsigned char* bytes;
    stbi_set_flip_vertically_on_load(true);
    stbi_ldr_to_hdr_gamma(1.0f);

    glGenTextures(1, &ID);
    glActiveTexture(slot);
    glBindTexture(texType, ID);

    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    if (format == GL_RGBA) {
        bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, STBI_rgb_alpha);
        glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, pixelType, bytes);
    }
    else if (format == GL_RGB) {
        bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, STBI_rgb);
        glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGB, pixelType, bytes);
    }
    else if (format == GL_RED) {
        bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 1);
        glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, GL_RED, pixelType, bytes);
    }
    else {
        bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);
        glTexImage2D(texType, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, pixelType, bytes);
    }
    glGenerateMipmap(texType);

    stbi_image_free(bytes);
    glBindTexture(texType, 0);
}

void Texture::texUnit(Shader shader, const char* uniform, GLuint unit)
{
    GLuint texUni = glGetUniformLocation(shader.ID, uniform);
    shader.Activate();
    glUniform1i(texUni, unit);
}

void Texture::Bind()
{
    glBindTexture(type, ID);
}

void Texture::Unbind()
{
    glBindTexture(type, 0);
}

void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}