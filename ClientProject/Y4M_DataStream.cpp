#include "Y4M_DataStream.h"
#include <QDebug>

Y4M_DataStream::Y4M_DataStream(std::string host, int port) : MediaDataStream(host, port)
{

}

char* Y4M_DataStream::getNextFrame()
{
    char* pFrame = nullptr;
    int curByteGetFromSocket = (*pSocketBuffer).size();
    //qDebug()<<"SZ_X:"<<curByteGetFromSocket;
    if( curByteGetFromSocket >= totalBytePerReceipt*(nCurrentReceipt+1))
    {
        if(curByteGetFromSocket-176444*(nCurrentReceipt+1)-curFrame*frameSize >= frameSize)
        {
            pFrame = new char[frameSize];
            size_t i=0;
            size_t j=offset;
            while(i<frameSize)
            {
                pFrame[i]=(*pSocketBuffer)[nCurrentReceipt*totalBytePerReceipt+176444+j];
                i++;
                j++;
                if(j==nByteOfFramePerReceipt)
                {
                    j=0;
                    nCurrentReceipt++;
                }
            }
            offset=j;
            curFrame++;
        }
    }
    return pFrame;
}

void Y4M_DataStream::accept(MediaReaderVisitor *visitor)
{
    visitor->read_Y4M(this);
}
