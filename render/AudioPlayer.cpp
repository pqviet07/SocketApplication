#include "AudioPlayer.h"

AudioPlayer::AudioPlayer()
{
    audioPlayer = new QMediaPlayer;
    QFile file("/home/quocviet/Desktop/ZaloProject/SocketApplication/render/asd33121.wav");
    file.open(QIODevice::ReadOnly);
    QByteArray arr = file.readAll();
    std::string stdString(arr.constData(), arr.length());
    QBuffer *buffer = new QBuffer(audioPlayer);
    buffer->setData(stdString.c_str(), stdString.size());

    buffer->open(QIODevice::ReadOnly);
    audioPlayer->setMedia(QMediaContent(), buffer);
    audioPlayer->play();
}

AudioPlayer::~AudioPlayer()
{
    delete audioPlayer;
}

