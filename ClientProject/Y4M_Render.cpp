#include <Y4M_Render.h>
Y4M_Render::Y4M_Render( MainWindow* mainWindow, Y4M_DataStream *y4mDataStream, size_t start)
{
    this->mainWindow = mainWindow;
    this->y4mDataStream = y4mDataStream;
    this->startTime = start;
}

char* Y4M_Render::readNextFrame()
{
    return y4mDataStream->getNextFrame();
}

void Y4M_Render::run()
{
    int width = y4mDataStream->getWidth();
    int height = y4mDataStream->getHeight();
    int fps = y4mDataStream->getFPS();
    int timeRenderPerFrame = round(1001/fps);

    while(true)
    {
        char* yuvData = readNextFrame();
        if(yuvData==nullptr) {
            QThread::msleep(4);
            continue;
        }

        emit letDisplayImage(yuvData, width, height);
        yuvData = nullptr;

        auto currTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        if(y4mDataStream->getCurFrame() == (int)(1+(currTime-startTime)/timeRenderPerFrame))
        {
            QThread::msleep(timeRenderPerFrame-(currTime-startTime)%timeRenderPerFrame);
        }
    }
}
