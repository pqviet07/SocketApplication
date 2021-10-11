#include <QApplication>
#include <QtWidgets>
#include <Y4M_Render.h>
#include <WAV_Render.h>
#include <WAV_DataStream.h>
#include <Y4M_DataStream.h>
#include <MediaFrameReader.h>
#include <MediaFrameSocketReader.h>
#include <QSound>
#include <QObject>
#include <chrono>
using namespace std::chrono;

int main(int argc, char** argv)
{
    QApplication *app = new QApplication(argc, argv);
    MainWindow *mainWindow= new MainWindow();

    // Test --------------------------------------------------------------------------
    MediaFrameReader *frameSocketReader = new MediaFrameSocketReader("127.0.0.1", 8889, true);
    auto startTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    std::mutex* g_mutex_video = new std::mutex();
    std::condition_variable *g_conditionVariable_video = new std::condition_variable();
    bool *g_ready_video = new bool;

    Y4M_DataStream *y4m_stream = new Y4M_DataStream(frameSocketReader);
    y4m_stream->setMutex(g_mutex_video);
    y4m_stream->setConditionVariable(g_conditionVariable_video);
    y4m_stream->setReady(g_ready_video);


    std::mutex* g_mutex_audio = new std::mutex();
    std::condition_variable *g_conditionVariable_audio = new std::condition_variable();
    bool *g_ready_audio = new bool;

    WAV_DataStream *wav_stream = new WAV_DataStream(frameSocketReader);
    wav_stream->setMutex(g_mutex_audio);
    wav_stream->setConditionVariable(g_conditionVariable_audio);
    wav_stream->setReady(g_ready_audio);

    Y4M_Render *y4m_render = new Y4M_Render(mainWindow, y4m_stream, startTime);
    WAV_Render *audio_render = new WAV_Render(mainWindow, wav_stream, startTime);

    QObject::connect(audio_render, &WAV_Render::letPlayAudio, mainWindow, &MainWindow::playAudio);
    QObject::connect(y4m_render, &Y4M_Render::letDisplayImage, mainWindow, &MainWindow::displayImage);


    y4m_stream->start();
    y4m_render->start();

    wav_stream->start();
    audio_render->start();
    // --------------------------------------------------------------------------------

    return app->exec();
}
