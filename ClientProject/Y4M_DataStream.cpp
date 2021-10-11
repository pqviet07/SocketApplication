#include "Y4M_DataStream.h"
#include <QDebug>

Y4M_DataStream::Y4M_DataStream(MediaFrameReader *frameReader) : MediaDataStream(frameReader)
{
    Y4M_Header *header = (Y4M_Header*)frameReader->getHeader(this);

    if(header)
    {
        width = header->width;
        height = header->height;
        fps = header->fps;
        frameSize = header->frameSize;
        duration = header->duration;
        nByteOfFramePerReceipt = header->nByteOfFramePerReceipt;
        totalBytePerReceipt = header->totalBytePerReceipt;
    }
}

char* Y4M_DataStream::getNextFrame()
{
    pBufferCurrentFrame = frameReader->readNextFrame(this);
    return pBufferCurrentFrame;
}

void Y4M_DataStream::setFrameReader(MediaFrameReader* frameReader)
{
    this->frameReader = frameReader;
}

void Y4M_DataStream::run()
{
    while (true)
    {
        std::unique_lock<std::mutex> ul(*g_mutex);
        // produce data
        if(getNextFrame()==nullptr)
        {
            continue;
        }
        *g_ready = true;

        ul.unlock();
        g_cv->notify_one();

        // wait consumer (render)
        ul.lock();
        g_cv->wait(ul, [&]{ return !(*g_ready); } );
    }
}

size_t Y4M_DataStream::getOffset() const
{
    return offset;
}

void Y4M_DataStream::setOffset(size_t offset)
{
    this->offset = offset;
}

int Y4M_DataStream::getWidth() const
{
    return width;
}

void Y4M_DataStream::setWidth(int width)
{
    this->width = width;
}

int Y4M_DataStream::getHeight() const
{
    return height;
}

void Y4M_DataStream::setHeight(int height)
{
    this->height = height;
}

int Y4M_DataStream::getFPS() const
{
    return fps;
}

void Y4M_DataStream::setFPS(int fps)
{
    this->fps = fps;
}

int Y4M_DataStream::getCurFrame() const
{
    return curFrame;
}

void Y4M_DataStream::setCurFrame(int curFrame)
{
    this->curFrame = curFrame;
}
