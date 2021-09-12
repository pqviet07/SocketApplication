#ifndef MYWINDOW_H
#define MYWINDOW_H
#include <QtWidgets>
#include <QLabel>
#include <QImage>
#include <QLayout>
#include <QPushButton>
#include <QPushButton>
#include <QObject>
#include <QSound>
#include <QMediaPlayer>

class MyWindow : public QWidget
{
private:
    QLabel *imageLabel{nullptr};
    QPushButton *pauseButton{nullptr};
    QPushButton *playButton{nullptr};
    QSound *sound{nullptr};
    bool isPause{false};
    QMediaPlayer *audioPlayer{nullptr};
public Q_SLOTS:
    void playVideo();
    void pauseVideo();
public:
    MyWindow();
    void displayVideo(std::string*, int, int);
    bool IsPause() const;
    virtual ~MyWindow() {}


};

#endif // MYWINDOW_H
