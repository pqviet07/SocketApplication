#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets>
#include <QLabel>
#include <QImage>
#include <QLayout>
#include <QPushButton>
#include <QPushButton>
#include <QObject>
#include <QSound>
#include <QMediaPlayer>

class MainWindow : public QWidget
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
    void playAudio(char*,int);

public:
    MainWindow();
    void displayImage(char*, int, int);
    bool IsPause() const;
    virtual ~MainWindow() {}
};

#endif // MAINWINDOW_H
