#include "WAV_Render.h"

WAV_Render::WAV_Render(MainWindow *mainWindow, WAV_DataStream *wavDataStream, long start)
{
    this->mainWindow = mainWindow;
    this->wavDataStream = wavDataStream;
    this->startTime = start;

    this->g_mutex = this->wavDataStream->getMutex();
    this->g_cv = this->wavDataStream->getConditionVariable();
    this->g_ready = this->wavDataStream->getReady();
}

char* WAV_Render::getNextFrame()
{
     pBufferCurrentFrame = wavDataStream->getBufferCurrentFrame();
     return pBufferCurrentFrame;
}

void WAV_Render::run()
{
    int duration = wavDataStream->getDuration();
    while(true)
    {

        std::unique_lock<std::mutex> ul(*g_mutex);
        g_cv->wait(ul, [&] { return *g_ready; });
        //qDebug()<<"In wav render";
        char* wavData = getNextFrame();

        *g_ready=false;

        emit letPlayAudio(wavData, wavDataStream->getFrameSize());

        auto currTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        if(wavDataStream->getNumberCurrentFrame() == (int)(1+(currTime-startTime)/duration))
        {
            QThread::msleep(duration);
        }

        ul.unlock();
        // notify to producer (y4mDataStream)
        g_cv->notify_one();

    }
}
