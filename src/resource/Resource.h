#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>


class IResource
{
public:
	virtual ~IResource() = default;
};


class Texture : public IResource
{
private:
    GLuint id_;
    int width_, height_, channels_;
public:
    Texture(GLuint id, int width, int height, int channels);
    ~Texture();

    void bind(GLenum target = GL_TEXTURE_2D) const;
    void activate(GLenum slot) const;

    GLuint id() const;
    int width() const;
    int height() const;
};


class Shader : public IResource 
{
public:
	Shader(const std::string& vertexShader, const std::string& fragmentShader);
	~Shader();
	void use();
	bool is_compiled() const;
	GLuint id() const;
private:
	//bool loadShader(const std::string& source, GLenum shaderType, GLuint& shaderID); -  גûםוסעט ג כמאהונ
	GLuint id_;
	bool is_compiled_;
};

