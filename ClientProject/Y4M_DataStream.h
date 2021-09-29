#ifndef Y4M_DATASTREAM_H
#define Y4M_DATASTREAM_H
#include <string>
#include <MediaDataStream.h>

class Y4M_DataStream : public MediaDataStream
{
private:
    int width{};
    int height{};
    int fps{24};
    int curFrame{0};
//    size_t frameSize{345600};
//    size_t nByteOfFramePerReceipt{24*345600};
//    size_t totalBytePerReceipt{8470844};
//    size_t curReceipt{0};
//    size_t curByte{0};
    size_t offset{0};

public:
    char* getNextFrame() override;
    void setFrameReader(MediaFrameReader*)override;

    size_t getOffset() const;
    void setOffset(size_t);

    int getWidth() const;
    void setWidth(int);

    int getHeight() const;
    void setHeight(int);

    int getFPS() const;
    void setFPS(int);

    int getCurFrame() const;
    void setCurFrame(int);
};

#endif
