#ifndef WAV_DATASTREAM_H
#define WAV_DATASTREAM_H
#include <vector>
#include <string>
#include <MediaDataStream.h>

class WAV_DataStream : public MediaDataStream {
public:
    WAV_DataStream(std::string host, int port);
    char* getNextFrame() override;
    void accept(MediaReaderVisitor* visitor) override;
    size_t getFrameSize() const;
};

#endif
