#ifndef WAV_RENDER_H
#define WAV_RENDER_H
#include <QThread>
#include <QFile>
#include <MainWindow.h>
#include <WAV_DataStream.h>
#include <QBuffer>
using namespace std::chrono;

class WAV_Render : public QThread
{
    Q_OBJECT;
Q_SIGNALS:
    void letPlayAudio(char*, int);

private:
    WAV_DataStream *wavDataStream{nullptr};
    MainWindow *mainWindow{nullptr};
    long startTime;
    char* pBufferCurrentFrame;

    std::mutex *g_mutex;
    std::condition_variable *g_cv;
    bool *g_ready;

public:
    WAV_Render(MainWindow*, WAV_DataStream*, long);
    char* getNextFrame();
    void run() override;
};

#endif // WAV_RENDER_H
