#include <YUV_Render.h>
YUV_Render::YUV_Render( MainWindow* mainWindow, Y4M_DataStream *y4mDataStream, long start)
{
    this->mainWindow = mainWindow;
    this->y4mDataStream = y4mDataStream;
    this->startTime = start;
}

char* YUV_Render::readNextFrame()
{
    return y4mDataStream->getNextFrame();
}

void YUV_Render::run()
{
    int width = y4mDataStream->getWidth();
    int height = y4mDataStream->getHeight();
    int fps = y4mDataStream->getFPS();

    while(true)
    {
        char* yuvData = readNextFrame();
        if(yuvData==nullptr) {
            QThread::msleep(10);
            continue;
        }

        mainWindow->displayVideo(yuvData, width, height);
        yuvData = nullptr;
        QThread::msleep(1000/fps - 17);
    }
}
