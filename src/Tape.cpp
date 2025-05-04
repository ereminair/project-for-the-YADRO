#include "Tape.h"
#include <iostream>

Tape::Tape(const std::string& path) : filename(path), head(0) {
    file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        file.open(filename, std::ios::out);
        file.close();
        file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    }
}

Tape::~Tape() {
    file.close();
}

int Tape::read() {
    file.seekg(head * sizeof(int));
    int value;
    file.read(reinterpret_cast<char*>(&value), sizeof(int));
    return value;
}

void Tape::write(int value) {
    file.seekp(head * sizeof(int));
    file.write(reinterpret_cast<char*>(&value), sizeof(int));
}

void Tape::moveLeft() {
    if (head > 0) head--;
}

void Tape::moveRight() {
    head++;
}

void Tape::rewind() {
    head = 0;
}

bool Tape::eof() {
    file.seekg(0, std::ios::end);
    return head * sizeof(int) >= file.tellg();
}