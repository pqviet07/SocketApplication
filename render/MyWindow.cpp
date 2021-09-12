#include <MyWindow.h>

void MyWindow::playVideo()
{
    isPause=false;
    audioPlayer->play();
}
void MyWindow::pauseVideo()
{
    isPause=true;
    audioPlayer->pause();
}
bool MyWindow::IsPause() const
{
    return isPause;
}

MyWindow::MyWindow() : QWidget()
{
    QWidget *window = new QWidget;
    window->setGeometry(100,100,800,600);
    QVBoxLayout* layout= new QVBoxLayout;
    // để tạm: ---------------------------
    audioPlayer = new QMediaPlayer;
    QFile file("/home/quocviet/Desktop/SocketApplication/raw_audio.wav");
    file.open(QIODevice::ReadOnly);
    QByteArray arr = file.readAll();
    QBuffer *buffer = new QBuffer(audioPlayer);
    buffer->setData(arr);
    buffer->open(QIODevice::ReadOnly);
    audioPlayer->setMedia(QMediaContent(), buffer);
    audioPlayer->play();
    //-------------------------------------
    imageLabel = new QLabel;
    pauseButton = new QPushButton("Pause");
    playButton = new QPushButton("Play");
    layout->addWidget(imageLabel);
    layout->addWidget(pauseButton);
    layout->addWidget(playButton);
    QObject::connect(pauseButton, &QPushButton::pressed, this, &MyWindow::pauseVideo);
    QObject::connect(playButton, &QPushButton::pressed, this, &MyWindow::playVideo);
    window->setLayout(layout);
    window->show();
}

void MyWindow::displayVideo(std::string* yuvData, int width, int height)
{
    QImage *myImage= new QImage(width, height, QImage::Format_ARGB32);

    for(int i=0; i<height; i++)
    {
        for(int j=0;j<width; j++)
        {
            int Y = 0xFF & (*yuvData)[(i * width) + j];
            int dx = ((i / 2) * (width / 2)) + (j / 2);
            int U = 0xFF & (*yuvData)[width*height + dx];
            int V = 0xFF & (*yuvData)[width*height+width*height/4 + dx];

            int r = Y + (1.370705f * (V-128));
            int g = Y - (0.698001f * (V-128)) - (0.337633f * (U-128));
            int b = Y + (1.732446f * (U-128));

            myImage->setPixel(j, i, qRgb(r, g, b));
        }
    }

    imageLabel->setPixmap(QPixmap::fromImage(*myImage));
    delete yuvData;
}
