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
    QThread::sleep(1);

    auto startTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    qDebug() <<startTime;

    Y4M_DataStream *y4m_stream = new Y4M_DataStream(frameSocketReader);
    WAV_DataStream *wav_stream = new WAV_DataStream(frameSocketReader);

    Y4M_Render *y4m_render = new Y4M_Render(mainWindow, y4m_stream, startTime);
    WAV_Render *audio_render = new WAV_Render(mainWindow, wav_stream, startTime);

    QObject::connect(audio_render, &WAV_Render::letPlayAudio, mainWindow, &MainWindow::playAudio);
    QObject::connect(y4m_render, &Y4M_Render::letDisplayImage, mainWindow, &MainWindow::displayImage);

    y4m_render->start();
    audio_render->start();
    // --------------------------------------------------------------------------------

    return app->exec();
}
