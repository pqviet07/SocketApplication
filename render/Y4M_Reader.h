#ifndef Y4M_READER_H
#define Y4M_READER_H
#include <bits/stdc++.h>

class Y4M_Reader
{
private:
    int width{};
    int height{};
    int fps{};
    size_t frameSize{345600};
    std::string path;
    std::string* pBuffer{nullptr};
    std::ifstream fin;

public:
    Y4M_Reader(std::string);
    std::string* getNextFrame();
    ~Y4M_Reader();
};

#endif
