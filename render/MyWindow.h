#ifndef MYWINDOW_H
#define MYWINDOW_H
#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QLayout>

class MyWindow : public QWidget
{
private:
    QLabel *imageLabel=nullptr;
public:
    MyWindow();
    void render(const QByteArray, int, int);
    virtual ~MyWindow() {}
};

#endif // MYWINDOW_H
