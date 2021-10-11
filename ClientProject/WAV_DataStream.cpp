#include "WAV_DataStream.h"
#include <QDebug>

WAV_DataStream::WAV_DataStream(MediaFrameReader *frameReader) : MediaDataStream(frameReader)
{
    WAV_Header *header = (WAV_Header*)frameReader->getHeader(this);
    duration = header->duration;
    frameSize = header->frameSize;
    totalBytePerReceipt = header->totalBytePerReceipt;
}

char* WAV_DataStream::getNextFrame()
{
    pBufferCurrentFrame = frameReader->readNextFrame(this);
    return pBufferCurrentFrame;
}

void WAV_DataStream::setFrameReader(MediaFrameReader* frameReader)
{
    this->frameReader = frameReader;
}

void WAV_DataStream::run()
{
    // int recvTime=0;
    while (true)
    {
        std::unique_lock<std::mutex> ul(*g_mutex);
        // produce data
        if(getNextFrame()==nullptr) continue;

        *g_ready = true;

        ul.unlock();
        g_cv->notify_one();
        // wait consumer (render)
        ul.lock();
        g_cv->wait(ul, [&]  { return !(*g_ready); } );
    }
}
