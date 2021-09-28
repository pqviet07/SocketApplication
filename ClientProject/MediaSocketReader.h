#ifndef MEDIASOCKETREADER_H
#define MEDIASOCKETREADER_H
#include <MediaReaderVisitor.h>

class MediaSocketReader
{
public:
    void read_WAV(const WAV_DataStream *element) const;
    void read_Y4M(const Y4M_DataStream *element) const;
};

#endif // MEDIASOCKETREADER_H
