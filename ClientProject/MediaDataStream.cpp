#include <MediaDataStream.h>
#include <QDebug>


std::mutex *MediaDataStream::getMutex()
{
    return g_mutex;
}

std::condition_variable *MediaDataStream::getConditionVariable()
{
    return g_cv;
}

bool *MediaDataStream::getReady()
{
    return g_ready;
}

void MediaDataStream::setMutex(std::mutex *value)
{
    g_mutex = value;
}

void MediaDataStream::setConditionVariable(std::condition_variable *value)
{
    g_cv = value;
}

void MediaDataStream::setReady(bool *value)
{
    g_ready = value;
}

MediaDataStream::MediaDataStream(MediaFrameReader *frameReader)
{
    this->frameReader = frameReader;
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



SocketDataStream *MediaDataStream::getSocketDataStream()
{
    return pSocketDataStream;
}

void MediaDataStream::setSocketDataStream(SocketDataStream *value)
{
    pSocketDataStream = value;
}

std::string *MediaDataStream::getBuffer() const
{
    return pbuffer;
}

void MediaDataStream::setBuffer(std::string *value)
{
    pbuffer = value;
}

char *MediaDataStream::getBufferCurrentFrame() const
{
    return pBufferCurrentFrame;
}

void MediaDataStream::setBufferCurrentFrame(char *value)
{
    pBufferCurrentFrame = value;
}
