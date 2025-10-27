#include "ResourceManager.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../external/stb_image/stb_image.h"

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
	stbi_set_flip_vertically_on_load(true); 

	int w, h, ch;
	unsigned char* data = loadTexture(path, &w, &h, &ch);
	

	std::shared_ptr<TextureObject> ptr = std::make_shared<TextureObject>(data, w, h, ch);


	if (!ptr) {
		std::cout << "texture not compiled\n";
		return nullptr;
	}

	textureMap.emplace(name, ptr);

	stbi_image_free(data);
	return ptr;
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
	mesh_map.erase(mesh_id);
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
	std::string fullPath = resPath + relatedPath;	
	unsigned char* data = stbi_load(fullPath.c_str(), width, height, channels, 0);

	if (!data) {
		std::cerr << "Error: Failed to load texture from " << fullPath << std::endl;
		return nullptr;
	}

	return data;
}

