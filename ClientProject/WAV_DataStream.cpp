#include "WAV_DataStream.h"
#include <QDebug>

char* WAV_DataStream::getNextFrame()
{
    return frameReader->readNextFrame(this);
}

void WAV_DataStream::setFrameReader(MediaFrameReader* frameReader)
{
    this->frameReader = frameReader;
}

size_t WAV_DataStream::getFrameSize() const
{
    return frameSize;
}
