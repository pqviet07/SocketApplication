#include "WAV_DataStream.h"
#include <QDebug>

WAV_DataStream::WAV_DataStream(MediaFrameReader *frameReader) : MediaDataStream(frameReader)
{}

char* WAV_DataStream::getNextFrame()
{
    return frameReader->readNextFrame(this);
}

void WAV_DataStream::setFrameReader(MediaFrameReader* frameReader)
{
    this->frameReader = frameReader;
}
