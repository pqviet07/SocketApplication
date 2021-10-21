#include <SocketReader.h>
#include <QDebug>

SocketReader *SocketReader::getInstance(std::string host, int port)
{
    static SocketReader instance(host, port);
    qDebug()<<&instance;
    return &instance;
}

SocketClient *SocketReader::getSocketClient()
{
    return socketClient;
}

void SocketReader::run()
{
    socketClient->connectToServer(host,port);
}

SocketReader::SocketReader(std::string host, int port)
{
    socketClient = new SocketClient;
    this->host=host;
    this->port=port;
}

SocketReader::~SocketReader()
{
    delete socketClient;

}
