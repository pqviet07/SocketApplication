#include <MediaDataStream.h>
#include <QDebug>

MediaDataStream::MediaDataStream(MediaFrameReader *frameReader)
{
    this->frameReader = frameReader;
    qDebug()<<"in media data stream";
}

int MediaDataStream::getFrameSize() const
{
    return frameSize;
}

void MediaDataStream::setFrameSize(const int &value)
{
    frameSize = value;
}

int MediaDataStream::getNumberByteOfFramePerReceipt() const
{
    return nByteOfFramePerReceipt;
}

void MediaDataStream::setNumberByteOfFramePerReceipt(const int &value)
{
    nByteOfFramePerReceipt = value;
}

int MediaDataStream::getTotalBytePerReceipt() const
{
    return totalBytePerReceipt;
}

void MediaDataStream::setTotalBytePerReceipt(const int &value)
{
    totalBytePerReceipt = value;
}

int MediaDataStream::getNumberCurrentFrame() const
{
    return nCurrentFrame;
}

void MediaDataStream::setNumberCurrentFrame(const int &value)
{
    nCurrentFrame = value;
}

int MediaDataStream::getNumberCurrentReceipt() const
{
    return nCurrentReceipt;
}

void MediaDataStream::setNumberCurrentReceipt(const int &value)
{
    nCurrentReceipt = value;
}

int MediaDataStream::getDuration() const
{
    return duration;
}

void MediaDataStream::setDuration(const int &value)
{
    duration = value;
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
