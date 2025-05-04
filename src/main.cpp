#include "Config.h"
#include "Sorter.h"
#include <iostream>

int main() {
    Config config = Config::loadFromFile("config.json");
    Sorter sorter(config.chunkSize);
    sorter.sort(config.inputPath, config.outputPath);
    std::cout << "Sorting complete.\n";
    return 0;
}
