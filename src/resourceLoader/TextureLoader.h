#pragma once
#include "../resource/Resource.h"

class TextureLoader
{
private:
	static std::string texture_path;
public:
	static std::shared_ptr<Texture> load(const std::string& path);
};
