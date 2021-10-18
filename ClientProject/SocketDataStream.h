#ifndef SOCKETDATASTREAM_H
#define SOCKETDATASTREAM_H
#include <mutex>
#include <condition_variable>
#include <vector>
#include <WAV_Header.h>
#include <Y4M_Header.h>
#include <atomic>

class SocketDataStream
{
private:
    std::vector<std::vector<char>> buffers;
    int bufferSize{0};
    int i{0},j{0};
    std::atomic<int> readIndexAudio{1};
    std::atomic<int> readIndexVideo{1};
    std::atomic<int> writeIndex{0};
    int totalSize{0};
    int headerSize{0};

    mutable std::mutex m_mutex[100];
    mutable std::condition_variable cv[100];

public:
    SocketDataStream(int sz);
    void push_back( const char& value );
    char operator[] (int) const;
    size_t size() const;

    int getReadIndexAudio() const;
    int getReadIndexVideo() const;
    int getWriteIndex() const;

    void incReadIndexAudio() ;
    void incReadIndexVideo() ;
    void incWriteIndex() ;

    std::mutex& getMutex(int idx);
    std::condition_variable& getConditionVariable(int idx);
};

#endif
