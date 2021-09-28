#include <MediaDataStream.h>

MediaDataStream::MediaDataStream(std::string host, int port)
{
    SocketReader *pSocketReader = SocketReader::getInstance(host,port);
    SocketClient *pSoketClient = pSocketReader->getSocketClient();
    pSocketBuffer =  pSoketClient->getDataStream();
    pSocketReader->start();
}

MediaDataStream::MediaDataStream(std::string path)
{

}
