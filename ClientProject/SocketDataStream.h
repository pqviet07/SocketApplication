#ifndef SOCKETDATASTREAM_H
#define SOCKETDATASTREAM_H
#include <mutex>
#include <condition_variable>
#include <vector>
#include <WAV_Header.h>
#include <Y4M_Header.h>

class SocketDataStream
{
private:
    std::vector<std::vector<char>> buffers;
    int bufferSize{0};
    int i{0};
    int readIndex{0};
    int writeIndex{0};
    int totalSize{0};
    int headerSize{0};

    mutable std::mutex m_mutex;
    std::condition_variable cv;

public:
    SocketDataStream(int sz);
    void push_back( const char& value );
    char operator[] (int) const;
    size_t size() const;

    int getReadIndex() const;
    int getWriteIndex() const;
    int setReadIndex(int) ;
    int setWriteIndex(int);
};

#endif
