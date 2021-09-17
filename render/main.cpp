#include <QApplication>
#include <QtWidgets>
#include <MyWindow.h>
#include <YUV_Render.h>
#include <Y4M_Reader.h>
#include <WAV_Reader.h>
#include <WAV_Render.h>
#include <AudioPlayer.h>
#include <QSound>
#include <QObject>

int main(int argc, char** argv)
{
    QApplication *app = new QApplication(argc, argv);

    MyWindow *mainWindow= new MyWindow();
    qDebug()<<mainWindow;

    // Test ------------------------------
    Y4M_Reader *y4m_reader = new Y4M_Reader("/home/quocviet/Desktop/SocketApplication/raw_video.y4m");
    WAV_Reader *wav_reader = new WAV_Reader("/home/quocviet/Desktop/SocketApplication/raw_audio.wav");

    YUV_Render *video_render = new YUV_Render(mainWindow, y4m_reader);
    WAV_Render *audio_render = new WAV_Render(mainWindow, wav_reader, 3000);
    QObject::connect(audio_render, &WAV_Render::letPlayAudio, mainWindow, &MyWindow::playAudio);

    video_render->start();
    audio_render->start();
    // -----------------------------------

    return app->exec();
}
