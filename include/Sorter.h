#pragma once
#include <string>

class Sorter {
public:
    explicit Sorter(int chunkSize);
    void sort(const std::string& inputPath, const std::string& outputPath);
private:
    int chunkSize_;
};

