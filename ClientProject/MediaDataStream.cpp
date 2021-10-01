#include <MediaDataStream.h>

size_t MediaDataStream::getFrameSize() const
{
    return frameSize;
}

void MediaDataStream::setFrameSize(const size_t &value)
{
    frameSize = value;
}

size_t MediaDataStream::getNumberByteOfFramePerReceipt() const
{
    return nByteOfFramePerReceipt;
}

void MediaDataStream::setNumberByteOfFramePerReceipt(const size_t &value)
{
    nByteOfFramePerReceipt = value;
}

size_t MediaDataStream::getTotalBytePerReceipt() const
{
    return totalBytePerReceipt;
}

void MediaDataStream::setTotalBytePerReceipt(const size_t &value)
{
    totalBytePerReceipt = value;
}

size_t MediaDataStream::getNumberCurrentFrame() const
{
    return nCurrentFrame;
}

void MediaDataStream::setNumberCurrentFrame(const size_t &value)
{
    nCurrentFrame = value;
}

size_t MediaDataStream::getNumberCurrentReceipt() const
{
    return nCurrentReceipt;
}

void MediaDataStream::setNumberCurrentReceipt(const size_t &value)
{
    nCurrentReceipt = value;
}

MediaDataStream::MediaDataStream(MediaFrameReader *frameReader)
{
    this->frameReader = frameReader;
}

SocketBuffer *MediaDataStream::getSocketBuffer()
{
    return pSocketBuffer;
}

void MediaDataStream::setSocketBuffer(SocketBuffer *value)
{
    pSocketBuffer = value;
}

std::string *MediaDataStream::getBuffer() const
{
    return pbuffer;
}

void MediaDataStream::setBuffer(std::string *value)
{
    pbuffer = value;
}
