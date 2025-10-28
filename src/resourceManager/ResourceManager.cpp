#include "ResourceManager.h"
#include <iostream>

void ResourceManager::add_resource(const std::string& id, std::shared_ptr<IResource> new_resource)
{
    resource_map[id] = std::move(new_resource);
}

bool ResourceManager::exist(const std::string& id)
{
    return resource_map.find(id) != resource_map.end();
}

std::shared_ptr<IResource> ResourceManager::get_resource(const std::string& id)
{
    auto it = resource_map.find(id);
    if (it != resource_map.end()) {
        return it->second;
    }
    return nullptr;
}

void ResourceManager::remove(const std::string& id)
{
    resource_map.erase(id);
}
