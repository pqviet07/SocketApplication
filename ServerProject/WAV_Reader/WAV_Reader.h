#ifndef WAV_READER_H
#define WAV_READER_H
#include <string>
#include <iostream>
#include <fstream>
#include "WAV_Data.h"

class WAV_Reader
{
private:
    WAV_Data *wavData{nullptr};
    std::string path;
    std::ifstream fin;

public:
    WAV_Reader(std::string path = "");
    std::string* getNextFrame(int duration);
    WAV_Header* readWavHeader();
    void showHeaderInfo();
    bool isEOF();
    ~WAV_Reader();
};

#endif
