#pragma once
#include <string>

struct Config {
    std::string inputPath;
    std::string outputPath;
    int chunkSize;

    static Config loadFromFile(const std::string& filename);
};
