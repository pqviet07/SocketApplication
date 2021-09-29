#include "Y4M_DataStream.h"
#include <QDebug>

char* Y4M_DataStream::getNextFrame()
{
    return frameReader->readNextFrame(this);
}

void Y4M_DataStream::setFrameReader(MediaFrameReader* frameReader)
{
    this->frameReader = frameReader;
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
