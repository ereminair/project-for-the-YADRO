#include "Config.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <stdexcept>

Config Config::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open config file: " + filename);
    }

    file.seekg(0, std::ios::end);
    if (file.tellg() == 0) {
        throw std::runtime_error("Config file is empty: " + filename);
    }
    file.seekg(0);

    nlohmann::json json;
    file >> json;

    Config config;
    config.inputPath = json["input"];
    config.outputPath = json["output"];
    config.chunkSize = json["chunkSize"];
    return config;
}
