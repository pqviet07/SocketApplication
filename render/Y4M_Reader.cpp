#include "Y4M_Reader.h"

Y4M_Reader::Y4M_Reader(std::string path)
{
    this->path = path;
    fin.open(this->path);
    if (!fin.is_open())
        return;

    std::string header;
    std::getline(fin, header);
    // TODO: handle header here!

    std::getline(fin, header);
}
Y4M_Reader::~Y4M_Reader()
{
    fin.close();
    delete pBuffer;
}

std::string* Y4M_Reader::getNextFrame()
{
    std::string* pFrame = new std::string();
    std::string temp;
    while(pFrame->size() < frameSize){
        std::getline(fin, temp);
        pFrame->append(temp);
        if(pFrame->size() == frameSize) pFrame->erase(pFrame->size() - 5, 5);
    }
    return pFrame;
}
