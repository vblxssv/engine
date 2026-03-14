#include "ShaderLoader.h"
#include <vector>
#include <fstream>
#include <sstream>

std::string ShaderLoader::shader_path = "../res/shaders/";


std::shared_ptr<Shader> ShaderLoader::load(const std::string& vertex_path, const std::string& fragment_path)
{
    try {
        // 1. Читаем исходники
        std::string vertexSrc = get_file_string(shader_path + vertex_path);
        std::string fragmentSrc = get_file_string(shader_path + fragment_path);

        // 2. Компилируем шейдеры
        GLuint vertexID, fragmentID;
        if (!load_shader(vertexSrc, GL_VERTEX_SHADER, vertexID)) {
            std::cerr << "Vertex shader compilation failed: " << vertex_path << std::endl;
            return nullptr;
        }
        if (!load_shader(fragmentSrc, GL_FRAGMENT_SHADER, fragmentID)) {
            std::cerr << "Fragment shader compilation failed: " << fragment_path << std::endl;
            return nullptr;
        }

        // 3. Создаём программу
        GLuint programID = glCreateProgram();
        glAttachShader(programID, vertexID);
        glAttachShader(programID, fragmentID);
        glLinkProgram(programID);

        // Проверка линковки
        GLint success;
        glGetProgramiv(programID, GL_LINK_STATUS, &success);
        if (success != GL_TRUE) {
            GLint logLength = 0;
            glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);
            if (logLength > 0) {
                std::vector<GLchar> log(logLength);
                glGetProgramInfoLog(programID, logLength, nullptr, log.data());
                std::cerr << "Shader program linking failed:\n" << log.data() << std::endl;
            }
            glDeleteProgram(programID);
            return nullptr;
        }

        // 4. Шейдеры больше не нужны после линковки
        glDeleteShader(vertexID);
        glDeleteShader(fragmentID);

        // 5. Возвращаем готовый Shader
        return std::make_shared<Shader>(programID);

    }
    catch (const std::exception& e) {
        std::cerr << "ShaderLoader error: " << e.what() << std::endl;
        return nullptr;
    }
}


bool ShaderLoader::load_shader(const std::string& source, GLenum shaderType, GLuint& shaderID)
{
    shaderID = glCreateShader(shaderType);
    const char* src = source.c_str();
    glShaderSource(shaderID, 1, &src, nullptr);
    glCompileShader(shaderID);

    GLint success;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (success == GL_TRUE) {
        return true;
    }

    GLint logLength = 0;
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        std::vector<GLchar> log(logLength);
        glGetShaderInfoLog(shaderID, logLength, nullptr, log.data());
        std::cerr << "Shader compilation failed:\n" << log.data() << std::endl;
    }

    glDeleteShader(shaderID);
    shaderID = 0;

    return false;
}

std::string ShaderLoader::get_file_string(const std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + path);
    }
    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}



