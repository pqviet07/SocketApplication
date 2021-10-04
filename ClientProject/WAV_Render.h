#ifndef WAV_RENDER_H
#define WAV_RENDER_H
#include <QThread>
#include <QFile>
#include <MainWindow.h>
#include <WAV_DataStream.h>
#include <QBuffer>

class WAV_Render : public QThread
{
    Q_OBJECT;
Q_SIGNALS:
    void letPlayAudio(char*, int);

private:
    WAV_DataStream *wavDataStream{nullptr};
    MainWindow *mainWindow{nullptr};
    long startTime;

public:
    WAV_Render(MainWindow*, WAV_DataStream*, long);
    char* readNextFrame();
    void run() override;
};

#endif // WAV_RENDER_H
