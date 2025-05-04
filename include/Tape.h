#pragma once
#include <fstream>
#include <string>

class Tape {
private:
    std::fstream file;
    std::string filename;
    int head;

public:
    Tape(const std::string& path);
    ~Tape();

    int read();
    void write(int value);
    void moveLeft();
    void moveRight();
    void rewind();
    bool eof();
};
