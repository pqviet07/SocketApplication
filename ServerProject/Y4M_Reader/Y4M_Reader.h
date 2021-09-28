#ifndef Y4M_READER_H
#define Y4M_READER_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <math.h>
#include "Y4M_Header.h"

const std::string STRING_BEGIN_FRAME = "FRAME";
const char PADDING_BYTE = 127;

class Y4M_Reader
{
private:
    Y4M_Header y4mHeader;
    int nCurrentFrame{1};
    int frameSize{0};
    std::string path;
    std::ifstream fin;

public:
    Y4M_Reader(std::string);
    std::string *getNextFrame();
    bool isEOF();
    ~Y4M_Reader();
    
    int getFrameSize() const;
    Y4M_Header getHeader() const;
    int getNumOfCurrentFrame() const;
};

#endif
