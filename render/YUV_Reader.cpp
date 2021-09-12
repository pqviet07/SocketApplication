#include <YUV_Reader.h>
#include <QDebug>
YUV_Reader::YUV_Reader(QString src, MyWindow* mainWindow)
{
    this->src = src;
    this->mainWindow = mainWindow;
}
void YUV_Reader::setSrc(QString src)
{
    this->src=src;
}

QByteArray* YUV_Reader::readData()
{
    if(src.size()==0) return nullptr;
    QFile file(src);
    file.open(QIODevice::ReadOnly);
    yuvData= new QByteArray;
    *yuvData = file.readAll();
    //ba.remove(ba.size()-1,1);
    file.close();
    //qDebug() << "read " << yuvData->size() << "bytes";
    return yuvData;

}

void YUV_Reader::run()
{
    // Test: render 2 images
    bool flag=true;
    int width=0;
    int height=0;

    while(true)
    {
        QThread::sleep(1);
        if(flag) {
            this->setSrc("/home/quocviet/Desktop/MediaPlayer/img24.yuv");
            width=150;
            height=200;
        }
        else
        {
            this->setSrc("/home/quocviet/Desktop/MediaPlayer/efg.yuv");
            width=640;
            height=360;
        }

        QByteArray* yuvData = readData();
        mainWindow->render(*yuvData, width, height);
        flag=!flag;
        qDebug()<<"Im here";
    }
}
