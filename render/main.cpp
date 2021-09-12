#include <QApplication>
#include <QtWidgets>
#include <MyWindow.h>
#include <YUV_Render.h>
#include <Y4M_Reader.h>
#include <QSound>

int main(int argc, char** argv)
{
    QApplication *app = new QApplication(argc, argv);

    MyWindow *mainWindow= new MyWindow();

    // Test ------------------------------
    Y4M_Reader *y4m_reader = new Y4M_Reader("/home/quocviet/Desktop/SocketApplication/raw_video.y4m");
    YUV_Render *render= new YUV_Render(mainWindow, y4m_reader);
    render->start();
    // -----------------------------------

    return app->exec();
}
