#ifndef WAV_HEADER_H
#define WAV_HEADER_H

struct WavHeader
{
    char riffId[4];
    unsigned int headerChunkSize;
    char waveId[4];

    char formatChunkId[4];
    unsigned int formatChunkSize;
    unsigned short compressionCode;
    unsigned short numberOfChannels;
    unsigned int samplesRate;
    unsigned int byteRate;
    unsigned short blockAlign;
    unsigned short bitsPerSample;

    char dataChunkId[4];
    unsigned int dataChunkSize;
};

#endif