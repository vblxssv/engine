#pragma once
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>

namespace IniParser {
    inline std::unordered_map<std::string, std::string> parse(const std::string& path) {
        std::unordered_map<std::string, std::string> result;
        std::ifstream file(path);
        if (!file.is_open())
            return result;

        std::string line;
        while (std::getline(file, line)) {
            // strip comments and whitespace
            auto comment = line.find('#');
            if (comment != std::string::npos)
                line = line.substr(0, comment);

            auto eq = line.find('=');
            if (eq == std::string::npos)
                continue;

            std::string key   = line.substr(0, eq);
            std::string value = line.substr(eq + 1);

            // trim whitespace
            auto trim = [](std::string& s) {
                size_t start = s.find_first_not_of(" \t\r\n");
                size_t end   = s.find_last_not_of(" \t\r\n");
                s = (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
            };
            trim(key);
            trim(value);

            if (!key.empty())
                result[key] = value;
        }
        return result;
    }
}
