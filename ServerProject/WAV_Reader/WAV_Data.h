#ifndef WAV_DATA_H
#define WAV_DATA_H

#include "WAV_Header.h"
#include <string>

struct WAV_Data
{
    WAV_Header header;
    std::string dataChunk;
};

#endif //
