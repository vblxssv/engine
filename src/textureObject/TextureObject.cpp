#include "TextureObject.h"

TextureObject::TextureObject(unsigned char* data, int width, int height, int chanels) :width(width), height(height), nChannels(chanels), textureID(0)
{
	
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	if (data) {
		GLenum format = (chanels == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		printf("Ошибка загрузки текстуры:\n");
}

TextureObject::~TextureObject()
{
	glDeleteTextures(1, &textureID);
}

void TextureObject::use()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

GLuint TextureObject::get_id()
{
	return textureID;
}

