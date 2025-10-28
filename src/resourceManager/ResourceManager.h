#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include "../resource/Resource.h"

class ResourceManager {
public:
	void add_resource(const std::string& id, std::shared_ptr<IResource> new_resource);
	bool exist(const std::string& id);
	std::shared_ptr<IResource> get_resource(const std::string& id);
	void remove(const std::string& id);
private:
	std::unordered_map<std::string, std::shared_ptr<IResource>> resource_map;
};





