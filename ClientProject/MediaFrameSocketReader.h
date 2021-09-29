#ifndef MEDIASOCKETREADER_H
#define MEDIASOCKETREADER_H
#include <MediaFrameReader.h>
#include <string>
#include <SocketReader.h>

class MediaFrameSocketReader : public MediaFrameReader
{
private:
    std::string host;
    int port;

public:
    MediaFrameSocketReader(std::string host, int port);
    void startAsync();
    void stopAsync();

    char* readNextFrame(WAV_DataStream*);
    char* readNextFrame(Y4M_DataStream*);
};

#endif // MEDIASOCKETREADER_H
