#ifndef WAV_DATA_H
#define WAV_DATA_H

#include "WAV_Header.h"
#include <vector>

struct WavData
{
    WavHeader header;
    std::vector<char> dataChunk;
};

#endif //