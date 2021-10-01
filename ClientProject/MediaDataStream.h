#ifndef MEDIADATASTREAM_H
#define MEDIADATASTREAM_H
#include <bits/stdc++.h>
#include <SocketReader.h>
#include <SocketBuffer.h>
#include <MediaFrameReader.h>

class MediaDataStream
{
protected:
    size_t frameSize;
    size_t nByteOfFramePerReceipt;
    size_t totalBytePerReceipt;
    size_t nCurrentFrame;
    size_t nCurrentReceipt;
    MediaFrameReader *frameReader;

    // from file
    std::string *pbuffer;
    // from socket
    SocketBuffer *pSocketBuffer;

public:
    MediaDataStream(MediaFrameReader *frameReader);
    virtual char* getNextFrame() = 0;
    virtual void setFrameReader(MediaFrameReader* frameReader) = 0;

    SocketBuffer *getSocketBuffer();
    void setSocketBuffer(SocketBuffer *value);

    std::string *getBuffer() const;
    void setBuffer(std::string *value);

    size_t getFrameSize() const;
    void setFrameSize(const size_t &value);

    size_t getNumberByteOfFramePerReceipt() const;
    void setNumberByteOfFramePerReceipt(const size_t &value);

    size_t getTotalBytePerReceipt() const;
    void setTotalBytePerReceipt(const size_t &value);

    size_t getNumberCurrentFrame() const;
    void setNumberCurrentFrame(const size_t &value);

    size_t getNumberCurrentReceipt() const;
    void setNumberCurrentReceipt(const size_t &value);
};

#endif // READER_H
