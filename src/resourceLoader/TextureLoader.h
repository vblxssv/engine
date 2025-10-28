#pragma once
#include "../resource/Resource.h"

class TextureLoader
{
public:
	static std::shared_ptr<Texture> load(const std::string& path);
};
