#ifndef MEDIAFILEREADER_H
#define MEDIAFILEREADER_H
#include <MediaReaderVisitor.h>

class MediaFileReader : public MediaReaderVisitor
{
public:
    void read_WAV(const WAV_DataStream *element) const;
    void read_Y4M(const Y4M_DataStream *element) const;
};

#endif // MEDIAFILEREADER_H
