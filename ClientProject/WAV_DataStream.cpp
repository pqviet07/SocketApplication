#include "WAV_DataStream.h"
#include <QDebug>

WAV_DataStream::WAV_DataStream(MediaFrameReader *frameReader) : MediaDataStream(frameReader)
{
    WAV_Header *header = (WAV_Header*)frameReader->getHeader(this);
    duration = header->duration;
    frameSize = header->frameSize;
    totalBytePerReceipt = header->totalBytePerReceipt;
    qDebug() << "Buff Size22: "<< totalBytePerReceipt;
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

    while (true)
    {
        std::unique_lock<std::mutex> ul(*g_mutex);
        // produce data

        // wait notify from socketdatastream
        std::mutex& mt= frameReader->getSocketDataStream()->getMutex(0);
        std::condition_variable& cv = frameReader->getSocketDataStream()->getConditionVariable(0);
        std::unique_lock<std::mutex> ul2(mt);
        // if read index < write index --> possible read data
        // else continue waiting
        cv.wait(ul2,[&]{return frameReader->getSocketDataStream()->getReadIndexAudio() < frameReader->getSocketDataStream()->getWriteIndex();});
        getNextFrame();
        //qDebug()<<"in wav datastream";
        frameReader->getSocketDataStream()->incReadIndexAudio();
        ul2.unlock();
        cv.notify_all();

        *g_ready = true;

        ul.unlock();
        g_cv->notify_all();
        // wait consumer (render)
        ul.lock();
        g_cv->wait(ul, [&]  { return !(*g_ready); } );
    }
}
