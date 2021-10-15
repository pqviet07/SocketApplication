#include <SocketDataStream.h>
#include <QDebug>

SocketDataStream::SocketDataStream(int sz)
{
    buffers.assign(sz, std::vector<char>());
    headerSize = sizeof(WAV_Header)+sizeof(Y4M_Header);
}

void SocketDataStream::push_back(const char& value)
{
    std::unique_lock<std::mutex> ul(m_mutex);
    cv.wait(ul, [&]{return readIndex<=writeIndex;});

    buffers[i].push_back(value);
     ++totalSize;

    if(i==0 && buffers[0].size()==sizeof(WAV_Header)+sizeof(Y4M_Header))
    {

        ++i;
        bufferSize = ((WAV_Header*)buffers[0].data())->totalBytePerReceipt;
        qDebug() << "Buff Size: "<< bufferSize;
        ++writeIndex;
    }
    else if(i!=0 && buffers[i].size()==bufferSize)
    {
        i=(i+1)%4;
        if(i==0) i==1;
        ++writeIndex;

        ul.unlock();
        cv.notify_all();
    }
}

// Map virtual idx to real idx
//  0  1  2  3  4               vec[0] store header
//  5  6  7  8  9 10 11 12      vec[1] store data
// 13 14 15 16 17 18 19 20      vec[2] store data
// 21 22 23 24 25 26 27 28      vec[3] store data
// 29 30 37 32 33 34 35 36      vec[4]--find in--->vec[1]
//                              vec[5]--find in--->vec[2]
char SocketDataStream::operator[](int idx) const
{
     // ReaderIdx < WritterIdx will Oke
     // if (1+(idx-headerSize)/bufferSize < writeIndex)
     int j{readIndex};
     if(readIndex>=buffers.size()) j=(readIndex+1)%buffers.size();
     return buffers[j][(idx-headerSize)%bufferSize];
}

size_t SocketDataStream::size() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return totalSize;
}

int SocketDataStream::getReadIndex() const
{
    return readIndex;
}

int SocketDataStream::getWriteIndex() const
{
    return writeIndex;
}

int SocketDataStream::setReadIndex(int value)
{
    readIndex=value;
}

int SocketDataStream::setWriteIndex(int value)
{
    writeIndex=value;
}

