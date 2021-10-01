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

int main(int argc, char** argv)
{
    QApplication *app = new QApplication(argc, argv);
    MainWindow *mainWindow= new MainWindow();

    // Test --------------------------------------------------------------------------
    MediaFrameReader *frameSocketReader = new MediaFrameSocketReader("127.0.0.1", 8889);

    Y4M_DataStream *y4m_stream = new Y4M_DataStream(frameSocketReader);
    WAV_DataStream *wav_stream = new WAV_DataStream(frameSocketReader);

    YUV_Render *yuv_render = new YUV_Render(mainWindow, y4m_stream);
    WAV_Render *audio_render = new WAV_Render(mainWindow, wav_stream);

    QObject::connect(audio_render, &WAV_Render::letPlayAudio, mainWindow, &MainWindow::playAudio);

    // start read data from socket
    frameSocketReader->startAsync();
    // start render
    yuv_render->start();
    audio_render->start();
    // --------------------------------------------------------------------------------

    return app->exec();
}
