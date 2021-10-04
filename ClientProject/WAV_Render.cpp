#include "WAV_Render.h"

WAV_Render::WAV_Render(MainWindow *mainWindow, WAV_DataStream *wavDataStream, size_t start)
{
    this->mainWindow = mainWindow;
    this->wavDataStream = wavDataStream;
    this->startTime = start;
}

char* WAV_Render::readNextFrame()
{
    return wavDataStream->getNextFrame();
}

void WAV_Render::run()
{
    int duration = wavDataStream->getDuration();
    while(true)
    {
        char* wavData = readNextFrame();
        if(wavData==nullptr) {
            QThread::msleep(4);
            continue;
        }

        emit letPlayAudio(wavData, wavDataStream->getFrameSize());
        auto currTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
        if(wavDataStream->getNumberCurrentFrame() == (int)(1+(currTime-startTime)/duration))
        {
            QThread::msleep(duration - (currTime-startTime)%duration);
        }
    }
}
