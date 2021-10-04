#include "WAV_Render.h"

WAV_Render::WAV_Render(MainWindow *mainWindow, WAV_DataStream *wavDataStream, long start)
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
            QThread::msleep(10);
            continue;
        }

        emit letPlayAudio(wavData, wavDataStream->getFrameSize());
        QThread::msleep(duration);
    }
}
