#ifndef WAV_DATA_H
#define WAV_DATA_H

#include "WAV_Header.h"
#include <string>

struct WavData
{
    WavHeader header;
    std::string dataChunk;
};

#endif //
