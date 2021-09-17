#ifndef WAV_READER_H
#define WAV_READER_H
#include <bits/stdc++.h>
#include "WAV_Data.h"

class WAV_Reader
{
private:
    //int duration{};
    WavData *wavData{nullptr};
    //std::vector<WavData> *splitedData{nullptr};
    std::string path;
    std::ifstream fin;

public:
    WAV_Reader(std::string path = "");
    std::string* getNextFrame(int duration);
    WavHeader* readWavHeader();
    //std::vector<WavData>* splitWavData(int secPerSegment = 1);
    void showHeaderInfo();
    ~WAV_Reader();

    //std::vector<char> *getWavData() const;
    //std::string getPath() const;
};

#endif
