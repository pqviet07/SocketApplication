#ifndef WAV_RENDER_H
#define WAV_RENDER_H
#include <QThread>
#include <QFile>
#include <MyWindow.h>
#include <WAV_Reader.h>
#include <QBuffer>
#include <AudioPlayer.h>

class WAV_Render : public QThread
{
    Q_OBJECT;
Q_SIGNALS:
    void letPlayAudio(std::string*);
private:
    std::string *wavData{nullptr};
    WAV_Reader *reader{nullptr};
    MyWindow *mainWindow{nullptr};
    QMediaPlayer *audioPlayer{nullptr};
    int duration{10};

public:
    WAV_Render(MyWindow*, WAV_Reader*, int duaration=10);
    std::string* readNextFrame();
    void run() override;
    
    void setInterval(int);
};
#endif // WAV_RENDER_H
