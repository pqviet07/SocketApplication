#include <QApplication>
#include <QtWidgets>
#include <MyWindow.h>
#include <YUV_Reader.h>

int main(int argc, char** argv)
{
    QApplication *app = new QApplication(argc, argv);

    MyWindow *mainWindow= new MyWindow();

    // Test ------------------------------
    YUV_Reader *reader = new YUV_Reader("/home/quocviet/Desktop/MediaPlayer/efg.yuv", mainWindow);
    reader->start();
    // -----------------------------------
    return app->exec();
}
