#include "ResourceManager.h"


ResourceManager::ResourceManager(const std::string& pathToRes)
{
	int index = pathToRes.find_last_of("\\");
	resPath = pathToRes.substr(0, index) + '\\' + "res\\";
}

ptrToProg ResourceManager::addProgram(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexSource = getFileString(vertexPath);
	std::string fragmentSource = getFileString(fragmentPath);

	ptrToProg newShaderProgram = std::make_shared<ShaderProgram>(vertexSource, fragmentSource);

	if (!newShaderProgram->compiled()) {
		std::cout << "Program not compiled\n";
		return nullptr;
	}

	shaderMap.emplace(name, newShaderProgram);

	return newShaderProgram;
}


ptrToProg ResourceManager::getProgram(const std::string& name)
{
	auto it = shaderMap.find(name);
	if (it != shaderMap.end()) {
		return it->second; 
	}
	return nullptr; 
}

ptrToTO ResourceManager::addTexture(const std::string& name, const std::string& path)
{
	return nullptr;
}

ptrToTO ResourceManager::getTexture(const std::string& name)
{
	auto it = textureMap.find(name);
	if (it != textureMap.end()) {
		return it->second;
	}
	return nullptr;
}

void ResourceManager::remove(std::string& mesh_id)
{
}






std::string ResourceManager::getFileString(const std::string& relatedPath)
{
	std::string fullPath = resPath + relatedPath;
	std::ifstream file(fullPath);

	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file: " + fullPath);
	}

	std::ostringstream buffer;
	buffer << file.rdbuf(); 
	return buffer.str();    
}

unsigned char* ResourceManager::loadTexture(const std::string& relatedPath, int* width, int* height, int* channels)
{
	return nullptr;
}



