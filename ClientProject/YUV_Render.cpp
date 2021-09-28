#include <YUV_Render.h>
YUV_Render::YUV_Render( MainWindow* mainWindow, Y4M_DataStream *y4mDataStream)
{
    this->mainWindow = mainWindow;
    this->y4mDataStream = y4mDataStream;
}

char* YUV_Render::readNextFrame()
{
    return y4mDataStream->getNextFrame();
}

void YUV_Render::run()
{
    // Test YUV_Render:
    int width = 640;
    int height = 360;
    while(true)
    {
        char* yuvData = readNextFrame();
        if(yuvData==nullptr) {
            QThread::msleep(200);
            continue;
        }
        mainWindow->displayVideo(yuvData, width, height);
        yuvData = nullptr;
        QThread::msleep(1001/24-15);
    }
}
