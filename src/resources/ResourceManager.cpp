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

void ResourceManager::remove(const std::string& id)
{
    resource_map.erase(id);
}
