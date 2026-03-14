#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include "resources/Resource.h"


class ResourceManager {
public:
	void add_resource(const std::string& id, std::shared_ptr<IResource> new_resource);
	bool exist(const std::string& id);
	std::shared_ptr<IResource> get_resource(const std::string& id);
	void remove(const std::string& id);
private:
	std::unordered_map<std::string, std::shared_ptr<IResource>> resource_map;
};





//class ResourceManager { 
//public:
//	ResourceManager(const std::string& pathToRes);
//	ptrToProg addProgram(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
//	ptrToProg getProgram(const std::string& name); 
//	ptrToTO addTexture(const std::string& name, const std::string& path);
//	ptrToTO getTexture(const std::string& name);
//	const std::shared_ptr<Mesh>& get_mesh(std::string& mesh_id);
//	void set_mesh(std::string& mesh_id, std::shared_ptr<Mesh> mesh);
//	void remove(std::string& mesh_id); 
//private: 
//	std::string resPath;
//	progMap shaderMap; 
//	textMap textureMap; 
//	std::unordered_map<std::string, std::shared_ptr<Mesh>> mesh_map; 
//	std::string getFileString(const std::string& relatedPath); 
//	unsigned char* loadTexture(const std::string& relatedPath, int* width, int* height, int* channels); 
//};