#ifndef YUV_READER_H
#define YUV_READER_H
#include <QThread>
#include <QFile>
#include <MainWindow.h>
#include <Y4M_DataStream.h>
#include <WAV_DataStream.h>

class YUV_Render : public QThread
{
private:
    Y4M_DataStream *y4mDataStream{nullptr};
    MainWindow *mainWindow{nullptr};

public:
    YUV_Render(MainWindow*, Y4M_DataStream*);
    char* readNextFrame();
    void run() override;
};

#endif // YUV_READER_H
