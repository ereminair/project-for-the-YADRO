#include "Sorter.h"
#include "Tape.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <cstdio>

Sorter::Sorter(int chunkSize) : chunkSize_(chunkSize) {}

void Sorter::sort(const std::string& inputPath, const std::string& outputPath) {
    std::ifstream input(inputPath);
    if (!input.is_open()) {
        throw std::runtime_error("Failed to open input file: " + inputPath);
    }

    std::vector<std::string> tempFiles;
    std::vector<int> buffer;
    int x, fileIndex = 0;

    while (input >> x) {
        buffer.push_back(x);
        if (buffer.size() == chunkSize_) {
            std::sort(buffer.begin(), buffer.end());
            std::string tempName = "tmp_" + std::to_string(fileIndex++) + ".txt";
            std::ofstream tmp(tempName);
            if (!tmp.is_open()) throw std::runtime_error("Failed to create temp file");
            for (int v : buffer) tmp << v << " ";
            tempFiles.push_back(tempName);
            buffer.clear();
        }
    }

    if (!input.eof() && input.fail()) {
        throw std::runtime_error("Input file contains invalid data.");
    }

    if (!buffer.empty()) {
        std::sort(buffer.begin(), buffer.end());
        std::string tempName = "tmp_" + std::to_string(fileIndex++) + ".txt";
        std::ofstream tmp(tempName);
        if (!tmp.is_open()) throw std::runtime_error("Failed to create temp file");
        for (int v : buffer) tmp << v << " ";
        tempFiles.push_back(tempName);
    }

    input.close();

    std::vector<std::ifstream> temps;
    for (const std::string& name : tempFiles) {
        temps.emplace_back(name);
        if (!temps.back().is_open()) throw std::runtime_error("Failed to open temp file");
    }

    std::vector<int> values(temps.size());
    std::vector<bool> valid(temps.size(), true);
    std::ofstream output(outputPath);
    if (!output.is_open()) {
        throw std::runtime_error("Failed to open output file: " + outputPath);
    }

    for (size_t i = 0; i < temps.size(); ++i) {
        if (!(temps[i] >> values[i])) valid[i] = false;
    }

    while (true) {
        int minIndex = -1;
        for (size_t i = 0; i < values.size(); ++i) {
            if (valid[i] && (minIndex == -1 || values[i] < values[minIndex])) {
                minIndex = i;
            }
        }
        if (minIndex == -1) break;
        output << values[minIndex] << " ";
        if (!(temps[minIndex] >> values[minIndex])) valid[minIndex] = false;
    }

    output.close();

    for (const std::string& name : tempFiles) {
        std::remove(name.c_str());
    }
}
