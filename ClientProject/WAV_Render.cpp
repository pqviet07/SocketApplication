
#include "WAV_Render.h"

WAV_Render::WAV_Render(MainWindow *mainWindow, WAV_DataStream *wavDataStream)
{
    this->mainWindow = mainWindow;
    this->wavDataStream = wavDataStream;
}

char* WAV_Render::readNextFrame()
{
    return wavDataStream->getNextFrame();
}

void WAV_Render::run()
{
    while(true)
    {
        char* wavData = readNextFrame();
        if(wavData==nullptr) {
            QThread::msleep(100);
            continue;
        }
        emit letPlayAudio(wavData, wavDataStream->getFrameSize());
        QThread::msleep(1000);
    }
}
