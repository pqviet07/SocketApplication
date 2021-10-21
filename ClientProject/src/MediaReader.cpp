#include "MediaDataStream.h"

MediaDataStream::MediaDataStream(string path)
{

}

MediaDataStream::MediaDataStream(std::string host, int port)
{
    pSocketReader = SocketReader::getInstance(host,port);
    pSocketReader->start();
}
