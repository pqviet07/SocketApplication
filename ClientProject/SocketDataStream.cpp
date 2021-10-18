#include <SocketDataStream.h>
#include <QDebug>

SocketDataStream::SocketDataStream(int sz)
{
    buffers.assign(sz, std::vector<char>());
    headerSize = sizeof(WAV_Header)+sizeof(Y4M_Header);
}

void SocketDataStream::push_back(const char& value)
{
    std::unique_lock<std::mutex> ul(m_mutex[i]);
    cv[i].wait(ul, [&]{return (readIndexAudio<=writeIndex && readIndexVideo<=writeIndex) || writeIndex==0;});

    if(i==0) buffers[i].push_back(value);
    else {
        buffers[i][j++]=value;
    }
     ++totalSize;
    //qDebug() << "Total Size: "<< totalSize;

    if(i==0 && buffers[0].size()==sizeof(WAV_Header)+sizeof(Y4M_Header))
    {
        ++i; 
        bufferSize = ((WAV_Header*)buffers[0].data())->totalBytePerReceipt;
        for(int idx=1;idx<buffers.size();idx++) buffers[idx].resize(bufferSize);
        incWriteIndex();
    }
    else if(i!=0 && j==bufferSize)
    {
        j=0;
        i++;
        if(i==buffers.size()) i=1;
        incWriteIndex();
        //qDebug()<<"notify here!";
        ul.unlock();
        cv[i].notify_all();
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
     // Reader Idx < Writter Idx will Oke
     // if (1+(idx-headerSize)/bufferSize < writeIndex)
     int x=0;
     int k=idx;
     if(idx>headerSize)
     {
         k=(idx-headerSize)%bufferSize;
         x=1+(idx-headerSize)/bufferSize;
         if(x>=buffers.size()) {
             x=x%(buffers.size()-1);
             if(x==0) x=buffers.size()-1;
         }
     }
     //  qDebug()<<"X:"<<x;
     return buffers[x][k];
}

size_t SocketDataStream::size() const
{
    //std::lock_guard<std::mutex> lock(m_mutex);
    return totalSize;
}

int SocketDataStream::getReadIndexAudio() const
{
    return readIndexAudio.load();
}

int SocketDataStream::getReadIndexVideo() const
{
    return readIndexVideo.load();
}

int SocketDataStream::getWriteIndex() const
{
    return writeIndex.load();
}

void SocketDataStream::incReadIndexAudio()
{
    ++readIndexAudio;
}

void SocketDataStream::incReadIndexVideo()
{
    ++readIndexVideo;
}

void SocketDataStream::incWriteIndex()
{
    ++writeIndex;
}

// readIdx: 1 2 3   4 5 6   7 8 9
// idx      1 2 3   1 2 3   1 2 3
std::condition_variable& SocketDataStream::getConditionVariable(int x)
{
    int idx{0};
    if(x==0) {
        idx = readIndexAudio;
        if(idx>=buffers.size()) {
            idx=readIndexAudio%(buffers.size()-1);
            if(idx==0) idx=buffers.size()-1;
        }
        //qDebug()<<idx;
    }
    else{
        idx = readIndexVideo;
        if(idx>=buffers.size()) {
            idx=readIndexVideo%(buffers.size()-1);
            if(idx==0) idx=buffers.size()-1;
        }
        //qDebug()<<idx;
   }
   return ref(cv[idx]);
}

std::mutex& SocketDataStream::getMutex(int x)
{
    int idx{0};
    if(x==0) {
        idx = readIndexAudio;
        if(idx>=buffers.size()) {
            idx=readIndexAudio%(buffers.size()-1);
            if(idx==0) idx=buffers.size()-1;
        }
        //qDebug()<<idx;
    }
    else {
        idx = readIndexVideo;
        if(idx>=buffers.size()) {
            idx=readIndexVideo%(buffers.size()-1);
            if(idx==0) idx=buffers.size()-1;
        }
        //qDebug()<<idx;
    }
    return ref(m_mutex[idx]);
}


