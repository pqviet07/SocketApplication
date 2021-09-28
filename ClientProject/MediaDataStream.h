#ifndef MEDIADATASTREAM_H
#define MEDIADATASTREAM_H
#include <bits/stdc++.h>
#include <SocketReader.h>
#include <SocketBuffer.h>
#include <MediaReaderVisitor.h>

class MediaDataStream
{
protected:
    size_t frameSize;
    size_t nByteOfFramePerReceipt;
    size_t totalBytePerReceipt;
    size_t nCurrentFrame;
    size_t nCurrentReceipt;

    // from file
    std::string filePath;
    std::ifstream fin;
    std::string buffer;

    // from socket
    std::string host;
    int port;
    const SocketBuffer *pSocketBuffer;

public:
    MediaDataStream(std::string path);
    MediaDataStream(std::string host, int port);
    virtual char* getNextFrame() = 0;
    virtual void accept(MediaReaderVisitor* visitor) = 0;
};

#endif // READER_H
