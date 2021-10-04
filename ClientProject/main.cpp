#include <QApplication>
#include <QtWidgets>
#include <YUV_Render.h>
#include <WAV_Render.h>
#include <WAV_DataStream.h>
#include <Y4M_DataStream.h>
#include <MediaFrameReader.h>
#include <MediaFrameSocketReader.h>
#include <QSound>
#include <QObject>
#include <chrono>

int main(int argc, char** argv)
{
    QApplication *app = new QApplication(argc, argv);
    MainWindow *mainWindow= new MainWindow();

    // Test --------------------------------------------------------------------------
    MediaFrameReader *frameSocketReader = new MediaFrameSocketReader("127.0.0.1", 8889, true);
    QThread::sleep(1);

    auto start_time =  std::chrono::system_clock::now();
    long t = std::chrono::system_clock::to_time_t(start_time);

    Y4M_DataStream *y4m_stream = new Y4M_DataStream(frameSocketReader);
    WAV_DataStream *wav_stream = new WAV_DataStream(frameSocketReader);

    YUV_Render *yuv_render = new YUV_Render(mainWindow, y4m_stream, t);
    WAV_Render *audio_render = new WAV_Render(mainWindow, wav_stream, t);

    QObject::connect(audio_render, &WAV_Render::letPlayAudio, mainWindow, &MainWindow::playAudio);

    yuv_render->start();
    audio_render->start();
    // --------------------------------------------------------------------------------

    return app->exec();
}
