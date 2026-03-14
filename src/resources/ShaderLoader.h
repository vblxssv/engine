#pragma once
#include "resources/Resource.h"
#include <memory>

class ShaderLoader
{
public:
	static std::shared_ptr<Shader> load(const std::string& vertex_path, const std::string& fragment_path);
private:
	static std::string shader_path; 
	static bool load_shader(const std::string& source, GLenum shaderType, GLuint& shaderID);

	static std::string get_file_string(const std::string& path);
};