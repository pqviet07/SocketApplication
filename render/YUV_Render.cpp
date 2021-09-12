#include <YUV_Render.h>
YUV_Render::YUV_Render( MyWindow* mainWindow, Y4M_Reader *reader)
{
    this->mainWindow = mainWindow;
    this->reader = reader;
}
std::string* YUV_Render::readNextFrame()
{
    std::string *pstr = reader->getNextFrame();
    return pstr;
}

void YUV_Render::run()
{
    // Test render:
    int width = 640;
    int height = 360;

    while(true)
    {
        if(mainWindow->IsPause()) continue;
        QThread::msleep(1001/24-14);

        std::string* yuvData = readNextFrame();
        if(yuvData==nullptr) break;
        mainWindow->displayVideo(yuvData, width, height);
        yuvData=nullptr;

    }
}
