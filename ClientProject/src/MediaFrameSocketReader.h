#ifndef MEDIASOCKETREADER_H
#define MEDIASOCKETREADER_H
#include <MediaFrameReader.h>
#include <string>
#include <SocketDataStream.h>

class MediaFrameSocketReader : public MediaFrameReader
{
private:
    std::string host;
    int port;

public:
    MediaFrameSocketReader(std::string host, int port, bool start=false);
    void startAsync() override;
    void stopAsync() override;

    char* readNextFrame(WAV_DataStream*) override;
    char* readNextFrame(Y4M_DataStream*)override;

    char* getHeader(WAV_DataStream*) override;
    char* getHeader(Y4M_DataStream*) override;

    SocketDataStream *getSocketDataStream() override;
};

#endif // MEDIASOCKETREADER_H
