#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "../renderer/ShaderProgram.h"
#include "../geometry/Geometry.h"
#include "../textureObject/TextureObject.h"

typedef std::shared_ptr<ShaderProgram> ptrToProg;
typedef std::unordered_map<std::string, ptrToProg> progMap;
typedef std::unordered_map<std::string, ptrToTO> textMap;



class ResourceManager {
public:
	ResourceManager(const std::string& pathToRes);

	ptrToProg addProgram(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
	ptrToProg getProgram(const std::string& name);
	ptrToTO addTexture(const std::string& name, const std::string& path);
	ptrToTO getTexture(const std::string& name);
	const std::shared_ptr<Mesh>& get_mesh(std::string& mesh_id);
	void set_mesh(std::string& mesh_id, std::shared_ptr<Mesh> mesh);
	void remove(std::string& mesh_id);
private:
	std::string resPath;
	progMap shaderMap;
	textMap textureMap;
	std::unordered_map<std::string, std::shared_ptr<Mesh>> mesh_map;


	std::string getFileString(const std::string& relatedPath);
	unsigned char* loadTexture(const std::string& relatedPath, int* width, int* height, int* channels);
};





