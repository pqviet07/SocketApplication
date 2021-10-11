#ifndef Y4M_Render_H
#define Y4M_Render_H
#include <QThread>
#include <QFile>
#include <MainWindow.h>
#include <Y4M_DataStream.h>
#include <WAV_DataStream.h>
using namespace std::chrono;

class Y4M_Render : public QThread
{
    Q_OBJECT;
Q_SIGNALS:
    void letDisplayImage(char*, int, int);

private:
    Y4M_DataStream *y4mDataStream{nullptr};
    MainWindow *mainWindow{nullptr};
    long startTime;

    char* pBufferCurrentFrame;

    std::mutex *g_mutex;
    std::condition_variable *g_cv;
    bool *g_ready;

public:
    Y4M_Render(MainWindow*, Y4M_DataStream*, long);
    char* getNextFrame();
    void run() override;
};

#endif // Y4M_Render_H
