#include <MediaFrameSocketReader.h>
#include <WAV_DataStream.h>
#include <Y4M_DataStream.h>
#include <QDebug>


MediaFrameSocketReader::MediaFrameSocketReader(std::string host, int port, bool start)
{
    SocketReader::getInstance(host, port);
    this->host = host;
    this->port = port;
    this->pSocketDataStream = SocketReader::getInstance(host, port)->getSocketClient()->getDataStream();

    if(start) {
        startAsync();
    }
    QThread::sleep(1);
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
    if(pSocketDataStream==nullptr) return nullptr;

    int frameSize = pDataStream->getFrameSize();
    int totalBytePerReceipt = pDataStream->getTotalBytePerReceipt();
    int nCurrentReceipt = pDataStream->getNumberCurrentReceipt();
    int nCurrentFrame = pDataStream->getNumberCurrentFrame();
    int headerSize = sizeof(Y4M_Header) + sizeof (WAV_Header);

    char* pFrame = nullptr;
    int SocketDataStreamSize = pSocketDataStream->size();

    if(SocketDataStreamSize-headerSize >= totalBytePerReceipt*(nCurrentReceipt+2))
    {
        pFrame = new char[frameSize];
        for(int i=0; i<frameSize; i++) pFrame[i] = (*pSocketDataStream)[nCurrentReceipt*totalBytePerReceipt+i+headerSize];
        pDataStream->setNumberCurrentReceipt(nCurrentReceipt+1);
        pDataStream->setNumberCurrentFrame(nCurrentFrame+1);
    }
    return pFrame;
}

char *MediaFrameSocketReader::readNextFrame(Y4M_DataStream *pDataStream)
{

    if(pSocketDataStream==nullptr) return nullptr;

    int frameSize = pDataStream->getFrameSize();
    int totalBytePerReceipt = pDataStream->getTotalBytePerReceipt();
    int nCurrentReceipt = pDataStream->getNumberCurrentReceipt();
    int headerSize = sizeof(Y4M_Header) + sizeof (WAV_Header);
    int nAudioBytePerReceipt = totalBytePerReceipt-pDataStream->getNumberByteOfFramePerReceipt();

    char* pFrame = nullptr;
    int SocketDataStreamSize = pSocketDataStream->size();

    if(SocketDataStreamSize-headerSize >= totalBytePerReceipt*(nCurrentReceipt+2))
    {
        int curFrame = pDataStream->getCurFrame();

        if(SocketDataStreamSize-nAudioBytePerReceipt*(nCurrentReceipt+1)- curFrame*frameSize >= frameSize)
        {
            pFrame = new char[frameSize];
            int i=0;
            int j=pDataStream->getOffset();

            while(i<frameSize)
            {
                pFrame[i]=(*pSocketDataStream)[nCurrentReceipt*totalBytePerReceipt+nAudioBytePerReceipt+j+headerSize];

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

char *MediaFrameSocketReader::getHeader(WAV_DataStream* pDataStream)
{
    char* header= new char[sizeof(WAV_Header)];
    SocketDataStream* p = SocketReader::getInstance(host, port)->getSocketClient()->getDataStream();
    for(int i=0; i<sizeof(WAV_Header); i++)  header[i] = (*p)[i];
    return header;
}

char *MediaFrameSocketReader::getHeader(Y4M_DataStream* pDataStream)
{
    char* header= new char[sizeof(Y4M_Header)];
    SocketDataStream* p = SocketReader::getInstance(host, port)->getSocketClient()->getDataStream();
    for(int i=0; i<sizeof(Y4M_Header); i++)  header[i] = (*p)[sizeof(WAV_Header)+i];
    return header;
}

SocketDataStream *MediaFrameSocketReader::getSocketDataStream()
{
    return pSocketDataStream;
}

