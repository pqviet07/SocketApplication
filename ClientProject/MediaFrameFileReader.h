#ifndef MEDIAFILEREADER_H
#define MEDIAFILEREADER_H
#include <MediaFrameReader.h>
#include <string>
#include <fstream>

class MediaFrameFileReader : public MediaFrameReader
{
private:
    std::string path;
    std::ifstream fin;

public:
    MediaFrameFileReader(std::string path);
    void startAsync();
    void stopAsync();

    char* readNextFrame(WAV_DataStream*);
    char* readNextFrame(Y4M_DataStream*);
};

#endif // MEDIAFILEREADER_H
