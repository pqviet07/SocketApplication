#include "SocketClient.h"
#include <QDebug>

SocketClient::SocketClient()
{
}

int SocketClient::receive_data(int socket)
{
    long long  recv_size = 0,  read_size=1, packet_index = 1;
    char dataArray[10241];

    //Loop while we have not received the entire file yet
    struct timeval timeout = {60, 0};

    fd_set fds;
    int buffer_fd;

    while (read_size!=0)
    {
        FD_ZERO(&fds);
        FD_SET(socket, &fds);

        buffer_fd = select(FD_SETSIZE, &fds, NULL, NULL, &timeout);

        if (buffer_fd < 0) printf("error: bad file descriptor set.\n");
        if (buffer_fd == 0) {
            printf("error: buffer read timeout expired.\n");
            break;
        }

        if (buffer_fd > 0)
        {
            do
            {
                read_size = read(socket, dataArray, 10241);
            } while (read_size < 0);

            for(size_t i=0; i< read_size; i++) dataStream.push_back(dataArray[i]);

            recv_size += read_size;
            packet_index++;
        }
    }

    qDebug() << recv_size;
    qDebug() << "Image successfully Received!\n";
    return 1;
}

int SocketClient::connectToServer(std::string host, int port)
{
    int socket_desc;
    struct sockaddr_in server;

    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }

    memset(&server, 0, sizeof(server));
    server.sin_addr.s_addr = inet_addr(host.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    //Connect to remote server
    if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        std::cout << strerror(errno);
        close(socket_desc);
        puts("Connect Error");
        return 1;
    }

    qDebug()<<"Connected!";
    receive_data(socket_desc);

    close(socket_desc);
    return 0;
}

SocketDataStream* SocketClient::getDataStream()
{
    return &dataStream;
}

