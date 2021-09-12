#ifndef YUV_READER_H
#define YUV_READER_H
#include <QThread>
#include <QFile>
#include <MyWindow.h>
class YUV_Reader : public QThread
{
private:
    QByteArray* yuvData{nullptr};
    QString src;
    MyWindow *mainWindow{nullptr};
public:
    YUV_Reader(QString, MyWindow*);
    QByteArray* readData();
    void setSrc(QString);
    void run() override;
};

#endif // YUV_READER_H
