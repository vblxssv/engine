#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <memory>

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
    void activate(GLenum slot = GL_TEXTURE0) const;

    GLuint id() const;
    int width() const;
    int height() const;
};


class Shader : public IResource 
{
private:
    GLuint id_;
public:
	Shader(GLuint id);
	~Shader();

	void use();

    void set_uniform_uint(const std::string& name, GLuint value);
    void set_uniform_int(const std::string& name, GLint value);
    void set_uniform_float(const std::string& name, GLfloat value);
    void set_uniform_mat4(const std::string& name, const glm::mat4& mat4);

	GLuint id() const;
};

