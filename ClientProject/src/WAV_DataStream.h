#ifndef WAV_DATASTREAM_H
#define WAV_DATASTREAM_H
#include <vector>
#include <string>
#include <MediaDataStream.h>
#include <WAV_Header.h>

class WAV_DataStream : public MediaDataStream, public QThread {

private:
    std::vector<char*> accumulateWav;

public:
    WAV_DataStream(MediaFrameReader*);
    char* getNextFrame() override;
    void setFrameReader(MediaFrameReader*) override;

    void run() override;
};

#endif
