#include "WAV_DataStream.h"
#include <QDebug>

WAV_DataStream::WAV_DataStream(std::string host, int port) : MediaDataStream(host, port)
{

}

char* WAV_DataStream::getNextFrame()
{
    char* pFrame = nullptr;
    int nCurrentByteGetFromSocket = (*pSocketBuffer).size();
    if( nCurrentByteGetFromSocket >= totalBytePerReceipt*(nCurrentReceipt+1))
    {
        pFrame = new char[frameSize];
        for(size_t i=0; i<frameSize; i++) pFrame[i] = (*pSocketBuffer)[nCurrentReceipt*totalBytePerReceipt+i];
        nCurrentReceipt++;
    }
    return pFrame;
}

void WAV_DataStream::accept(MediaReaderVisitor *visitor)
{
    visitor->read_WAV(this);
}

size_t WAV_DataStream::getFrameSize() const
{
    return frameSize;
}
