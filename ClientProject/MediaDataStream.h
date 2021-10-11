#ifndef MEDIADATASTREAM_H
#define MEDIADATASTREAM_H
#include <bits/stdc++.h>
#include <SocketReader.h>
#include <SocketDataStream.h>
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
    SocketDataStream *pSocketDataStream;

    char *pBufferCurrentFrame;

    std::mutex *g_mutex;
    std::condition_variable *g_cv;
    bool *g_ready;

public:
    MediaDataStream(MediaFrameReader *frameReader);

    virtual char* getNextFrame() = 0;
    virtual void setFrameReader(MediaFrameReader* frameReader) = 0;

    SocketDataStream *getSocketDataStream();
    void setSocketDataStream(SocketDataStream *value);

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

    char *getBufferCurrentFrame() const;
    void setBufferCurrentFrame(char *value);

    std::mutex *getMutex();
    void setMutex(std::mutex *value);

    std::condition_variable *getConditionVariable();
    void setConditionVariable(std::condition_variable *value);

    bool *getReady();
    void setReady(bool *value);
};

#endif // READER_H
