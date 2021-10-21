#ifndef Y4M_DATASTREAM_H
#define Y4M_DATASTREAM_H
#include <string>
#include <MediaDataStream.h>
#include <Y4M_Header.h>

class Y4M_DataStream : public MediaDataStream, public QThread
{
private:
    int width{};
    int height{};
    int fps{24};
    int curFrame{0};
    size_t offset{0};

public:
    Y4M_DataStream(MediaFrameReader*);

    char* getNextFrame() override;
    void setFrameReader(MediaFrameReader*)override;

    void run() override;

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
