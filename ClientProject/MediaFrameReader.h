#ifndef MEDIAREADER_H
#define MEDIAREADER_H
//prevent circular dependencies
class WAV_DataStream;
class Y4M_DataStream;
//-----------------------------

class MediaFrameReader
{
public:
    virtual void startAsync() = 0;
    virtual void stopAsync() = 0;

    virtual char* readNextFrame(WAV_DataStream*) = 0;
    virtual char* readNextFrame(Y4M_DataStream*) = 0;

    virtual char* getHeader(WAV_DataStream*) = 0;
    virtual char* getHeader(Y4M_DataStream*) = 0;
};

#endif // MEDIAREADER_H
