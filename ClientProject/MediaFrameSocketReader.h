#ifndef MEDIASOCKETREADER_H
#define MEDIASOCKETREADER_H
#include <MediaFrameReader.h>
#include <string>
#include <SocketReader.h>
#include <SocketBuffer.h>

class MediaFrameSocketReader : public MediaFrameReader
{
private:
    std::string host;
    int port;
    SocketBuffer *pSocketBuffer;

public:
    MediaFrameSocketReader(std::string host, int port, bool start=false);
    void startAsync();
    void stopAsync();

    char* readNextFrame(WAV_DataStream*);
    char* readNextFrame(Y4M_DataStream*);

    char* getHeader(WAV_DataStream*);
    char* getHeader(Y4M_DataStream*);
};

#endif // MEDIASOCKETREADER_H
