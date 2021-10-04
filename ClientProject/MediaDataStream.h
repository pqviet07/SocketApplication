#ifndef MEDIADATASTREAM_H
#define MEDIADATASTREAM_H
#include <bits/stdc++.h>
#include <SocketReader.h>
#include <SocketBuffer.h>
#include <MediaFrameReader.h>

class MediaDataStream
{
protected:
    int frameSize{0};
    int nByteOfFramePerReceipt{0};
    int totalBytePerReceipt{0};
    int nCurrentFrame{0};
    int nCurrentReceipt{0};
    int duration{0};
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

    int getFrameSize() const;
    void setFrameSize(const int &value);

    int getNumberByteOfFramePerReceipt() const;
    void setNumberByteOfFramePerReceipt(const int &value);

    int getTotalBytePerReceipt() const;
    void setTotalBytePerReceipt(const int &value);

    int getNumberCurrentFrame() const;
    void setNumberCurrentFrame(const int &value);

    int getNumberCurrentReceipt() const;
    void setNumberCurrentReceipt(const int &value);

    int getDuration() const;
    void setDuration(const int &value);
};

#endif // READER_H
