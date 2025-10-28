#include "Resource.h"

Texture::Texture(GLuint id, int width, int height, int channels)
	: id_(id), width_(width), height_(height), channels_(channels)
{

}

Texture::~Texture()
{
	glDeleteTextures(1, &id_);
}

void Texture::bind(GLenum target = GL_TEXTURE_2D) const
{
	glBindTexture(target, id_);
}

void Texture::activate(GLenum slot = GL_TEXTURE0) const
{
	glActiveTexture(slot);
}

GLuint Texture::id() const
{
	return id_;
}

int Texture::width() const
{
	return width_;
}

int Texture::height() const
{
	return height_;
}

