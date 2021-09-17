#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H
#include <QThread>
#include <QFile>
#include <QMediaPlayer>
#include <QBuffer>
#include <QWidget>

class AudioPlayer
{
private:
    QMediaPlayer *audioPlayer{nullptr};
public:
    AudioPlayer();
    ~AudioPlayer();
};

#endif // AUDIOPLAYER_H
