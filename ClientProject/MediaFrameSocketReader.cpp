#include <MediaFrameSocketReader.h>
#include <MediaDataStream.h>
#include <WAV_DataStream.h>
#include <Y4M_DataStream.h>
MediaFrameSocketReader::MediaFrameSocketReader(std::string host, int port)
{
    SocketReader::getInstance(host, port);
    this->host = host;
    this->port = port;
}

void MediaFrameSocketReader::startAsync()
{
     SocketReader::getInstance(host, port)->start();
}

void MediaFrameSocketReader::stopAsync()
{
    SocketReader::getInstance(host, port);
}

char *MediaFrameSocketReader::readNextFrame(WAV_DataStream *pDataStream)
{
        SocketBuffer *pSocketBuffer = pDataStream->getSocketBuffer();
        size_t frameSize = pDataStream->getFrameSize();
        size_t totalBytePerReceipt = pDataStream->getTotalBytePerReceipt();
        size_t nCurrentReceipt = pDataStream->getNumberCurrentReceipt();

        char* pFrame = nullptr;
        size_t nCurrentByteGetFromSocket = (*pSocketBuffer).size();
        if( nCurrentByteGetFromSocket >= totalBytePerReceipt*(nCurrentReceipt+1))
        {
            pFrame = new char[frameSize];
            for(size_t i=0; i<frameSize; i++) pFrame[i] = (*pSocketBuffer)[nCurrentReceipt*totalBytePerReceipt+i];
            ++nCurrentReceipt;
            pDataStream->setNumberCurrentFrame(nCurrentReceipt);
        }
        return pFrame;
}

char *MediaFrameSocketReader::readNextFrame(Y4M_DataStream *pDataStream)
{
    SocketBuffer *pSocketBuffer = pDataStream->getSocketBuffer();
    size_t frameSize = pDataStream->getFrameSize();
    size_t totalBytePerReceipt = pDataStream->getTotalBytePerReceipt();
    size_t nCurrentReceipt = pDataStream->getNumberCurrentReceipt();

    char* pFrame = nullptr;
    size_t curByteGetFromSocket = (*pSocketBuffer).size();
    //qDebug()<<"SZ_X:"<<curByteGetFromSocket;
    if(curByteGetFromSocket >= totalBytePerReceipt*(nCurrentReceipt+1))
    {
        int curFrame = pDataStream->getCurFrame();
        if(curByteGetFromSocket-176444*(nCurrentReceipt+1)- curFrame*frameSize >= frameSize)
        {
            pFrame = new char[frameSize];
            size_t i=0;
            size_t j=pDataStream->getOffset();
            while(i<frameSize)
            {
                pFrame[i]=(*pSocketBuffer)[nCurrentReceipt*totalBytePerReceipt+176444+j];
                i++;
                j++;
                if(j==pDataStream->getNumberByteOfFramePerReceipt())
                {
                    j=0;
                    nCurrentReceipt++;
                    pDataStream->setNumberCurrentReceipt(nCurrentReceipt);
                }
            }
            pDataStream->setOffset(j);
            curFrame++;
            pDataStream->setCurFrame(curFrame);
        }
    }
    return pFrame;
}
