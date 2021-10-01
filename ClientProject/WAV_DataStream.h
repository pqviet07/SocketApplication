#ifndef WAV_DATASTREAM_H
#define WAV_DATASTREAM_H
#include <vector>
#include <string>
#include <MediaDataStream.h>

class WAV_DataStream : public MediaDataStream {

public:
    WAV_DataStream(MediaFrameReader*);
    char* getNextFrame() override;
    void setFrameReader(MediaFrameReader*) override;
};

#endif
