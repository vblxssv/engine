#pragma once
#include <string>
#include "core/IniParser.h"

struct AppConfig {
    int   width     = 1200;
    int   height    = 800;
    int   fps_limit = 75;
    float fov       = 90.f;

    static AppConfig from_file(const std::string& path) {
        AppConfig cfg;
        auto ini = IniParser::parse(path);

        auto get_int   = [&](const std::string& key, int&   dst) { if (ini.count(key)) dst = std::stoi(ini[key]); };
        auto get_float = [&](const std::string& key, float& dst) { if (ini.count(key)) dst = std::stof(ini[key]); };

        get_int  ("width",     cfg.width);
        get_int  ("height",    cfg.height);
        get_int  ("fps_limit", cfg.fps_limit);
        get_float("fov",       cfg.fov);

        return cfg;
    }
};
