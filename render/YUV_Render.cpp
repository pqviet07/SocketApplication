#include <YUV_Render.h>
YUV_Render::YUV_Render( MyWindow* mainWindow, Y4M_Reader *reader)
{
    this->mainWindow = mainWindow;
    this->reader = reader;
}

std::string* YUV_Render::readNextFrame()
{
    return reader->getNextFrame();
}

void YUV_Render::run()
{
    // Test render:
    int width = 640;
    int height = 360;

    while(true)
    {
        if(mainWindow->IsPause()) continue;

        std::string* yuvData = readNextFrame();
        if(yuvData==nullptr) break;
        mainWindow->displayVideo(yuvData, width, height);

        yuvData=nullptr;
        QThread::msleep(1001/24-14);
    }
}
