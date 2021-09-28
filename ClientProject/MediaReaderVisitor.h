#ifndef MEDIAREADERVISITOR_H
#define MEDIAREADERVISITOR_H
//prevent circular dependencies
class WAV_DataStream;
class Y4M_DataStream;
//-----------------------------

class MediaReaderVisitor
{
public:
    virtual void read_WAV(const WAV_DataStream *element) const = 0;
    virtual void read_Y4M(const Y4M_DataStream *element) const = 0;
};

#endif // MEDIAREADERVISITOR_H
