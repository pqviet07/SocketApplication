#include <MediaFrameFileReader.h>

MediaFrameFileReader::MediaFrameFileReader(std::string path)
{
    fin.open(path);
}

void MediaFrameFileReader::startAsync()
{

}

void MediaFrameFileReader::stopAsync()
{

}

char *MediaFrameFileReader::readNextFrame(WAV_DataStream *)
{

}

char *MediaFrameFileReader::readNextFrame(Y4M_DataStream *)
{

}

