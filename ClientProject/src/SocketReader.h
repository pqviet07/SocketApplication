#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>
#include <SocketClient.h>

class SocketReader : public QThread
{
private:
    SocketClient *socketClient{nullptr};
    std::string host;
    int port;

public:
    static SocketReader* getInstance(std::string, int);
    SocketClient *getSocketClient();
    void run() override;

private:
    SocketReader();
    SocketReader(std::string, int port);
    ~SocketReader();

};
#endif // MYTHREAD_H
