#include <Y4M_Render.h>

Y4M_Render::Y4M_Render( MainWindow* mainWindow, Y4M_DataStream *y4mDataStream, long start)
{
    this->mainWindow = mainWindow;
    this->y4mDataStream = y4mDataStream;
    this->startTime = start;

    this->g_mutex = this->y4mDataStream->getMutex();
    this->g_cv = this->y4mDataStream->getConditionVariable();
    this->g_ready = this->y4mDataStream->getReady();
}

char* Y4M_Render::getNextFrame()
{
    pBufferCurrentFrame = y4mDataStream->getBufferCurrentFrame();
    return pBufferCurrentFrame;
}

void Y4M_Render::run()
{
    int width = y4mDataStream->getWidth();
    int height = y4mDataStream->getHeight();
    int fps = y4mDataStream->getFPS();
    int timeRenderPerFrame = round(1001/fps);
    long lastTime = startTime;

    while(true)
    {
        std::unique_lock<std::mutex> ul(*g_mutex);
        g_cv->wait(ul, [&] { return *g_ready; });

       // qDebug()<<"In 4ym render";
        char* yuvData = getNextFrame();

        *g_ready=false;

        mainWindow->displayImage(yuvData, width, height);

        // calculate for decision making that should delay or not
        auto currTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        if(y4mDataStream->getCurFrame() == (int)(1+(currTime-startTime)/timeRenderPerFrame))
        {
            QThread::msleep(timeRenderPerFrame);
        }

        ul.unlock();
        // notify to producer (y4mDataStream)
        g_cv->notify_one();
    }
}
