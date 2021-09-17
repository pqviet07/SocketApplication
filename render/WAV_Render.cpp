
#include "WAV_Render.h"

WAV_Render::WAV_Render(MyWindow *mainWindow, WAV_Reader *reader, int duration)
{
    this->mainWindow = mainWindow;
    this->reader = reader;
    this->duration = duration;

}

std::string *WAV_Render::readNextFrame()
{
    return reader->getNextFrame(this->duration);
}

void WAV_Render::run()
{
    while(true)
    {
        if(mainWindow->IsPause()) continue;

        std::string* data=readNextFrame();
        if(data==nullptr) break;
        emit letPlayAudio(data);
        QThread::msleep(2985);
    }

}

void WAV_Render::setInterval(int duration)
{
    this->duration = duration;
}
