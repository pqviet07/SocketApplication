#include "Y4M_Reader.h"

Y4M_Reader::Y4M_Reader(std::string path)
{
    this->path = path;
    fin.open(this->path);
    if (!fin.is_open()) return;

    std::string headerStr;
    std::getline(fin, headerStr);

    // --------------------------- parse header -------------------------------------
    // split header
    std::istringstream iss(headerStr);
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(iss, token, ' '))
    {
        // remove prefix character of parameter 
        if(!tokens.empty()) token.erase(0, 1);
        tokens.push_back(token);
    }

    int idx = 0; 
    // parse file signature
    for (int i = 0; i < tokens[idx].size(); ++i) y4mHeader.signature[i] = tokens[idx][i];
    idx++;

    // parse width & height
    y4mHeader.width = stoi(tokens[idx++]);
    y4mHeader.height = stoi(tokens[idx++]);

    // parse FPS
    {
        std::istringstream iss(tokens[idx++]);
        
        std::getline(iss, token, ':');
        int nframe = stoi(token);
        
        std::getline(iss, token);
        int nsec = stoi(token);
        y4mHeader.fps = round(1.*nframe/nsec);
    }

    // parse interlacing_mode
    y4mHeader.interlacing_mode = tokens[idx++][0];

    // parse pixel ratio
    for (int i = 0; i < tokens[idx].size(); ++i) y4mHeader.pixel_ratio[i] = tokens[idx][i];
    idx++;

    // parse colour space
    for (int i = 0; i < tokens[idx].size(); ++i) y4mHeader.color_space[i] = tokens[idx][i];
    
    //------------------------------- properties computed from header ---------------------------------------
    int yuvRatio = stoi(std::string(y4mHeader.color_space).substr(0, 3));
    switch (yuvRatio)
    {
    case 420:
        frameSize = y4mHeader.width * y4mHeader.height * 3 / 2;
        break;
    case 422:
        frameSize = y4mHeader.width * y4mHeader.height * 2;
        break;
    case 444:
        frameSize = y4mHeader.width * y4mHeader.height * 3;
        break;
    default:
        std::cerr << "Not supported" << std::endl;
        break;
    }
    // -----------------------------------------------------------------------------------
    
    std::getline(fin, headerStr);
}

std::string *Y4M_Reader::getNextFrame()
{
    std::string *pFrame = new std::string;
    std::string temp;
    
    while (pFrame->size() < frameSize)
    {
        std::getline(fin, temp);
        pFrame->append(temp);
        
        if (pFrame->size() > frameSize)
        {
            std::string fiveOfLastByte = pFrame->substr(pFrame->size() - STRING_BEGIN_FRAME.size(), STRING_BEGIN_FRAME.size());
            if(fiveOfLastByte == STRING_BEGIN_FRAME)
            {
                pFrame->erase(pFrame->size() - STRING_BEGIN_FRAME.size(), STRING_BEGIN_FRAME.size());
                int nPadding = frameSize - pFrame->size();
                for (int i = 0; i < nPadding; ++i) pFrame->push_back(PADDING_BYTE);
                break;
            }
        }
    }
    ++nCurrentFrame;
    return pFrame;
}

Y4M_Reader::~Y4M_Reader() { if(fin.is_open()) fin.close(); }

bool Y4M_Reader::isEOF() { return fin.eof(); }

int Y4M_Reader::getFrameSize() const { return frameSize; }

Y4M_Header Y4M_Reader::getHeader() const { return y4mHeader; }

int Y4M_Reader::getNumOfCurrentFrame() const { return nCurrentFrame; }
