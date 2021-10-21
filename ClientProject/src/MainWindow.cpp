#include <MainWindow.h>

void MainWindow::playVideo()
{
    isPause=false;
    audioPlayer->play();
}
void MainWindow::pauseVideo()
{
    isPause=true;
    audioPlayer->pause();
}
bool MainWindow::IsPause() const
{
    return isPause;
}

MainWindow::MainWindow() : QWidget()
{
    QWidget *window = new QWidget;
    window->setGeometry(20,20,800,600);
    QVBoxLayout* layout= new QVBoxLayout;

    imageLabel = new QLabel;
    pauseButton = new QPushButton("Pause");
    playButton = new QPushButton("Play");
    layout->addWidget(imageLabel);
    layout->addWidget(pauseButton);
    layout->addWidget(playButton);
    QObject::connect(pauseButton, &QPushButton::pressed, this, &MainWindow::pauseVideo);
    QObject::connect(playButton, &QPushButton::pressed, this, &MainWindow::playVideo);
    window->setLayout(layout);
    window->show();
}

void MainWindow::displayImage(char* yuvData, int width, int height)
{

    auto start = std::chrono::high_resolution_clock::now();

    QImage myImage(width, height, QImage::Format_ARGB32);

    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            int Y = 0xFF & yuvData[(i * width) + j];
            int dx = ((i / 2) * (width / 2)) + (j / 2);
            int U = 0xFF & yuvData[width*height + dx];
            int V = 0xFF & yuvData[width*height+width*height/4 + dx];

            int r = Y + (1.370705f * (V-128));
            int g = Y - (0.698001f * (V-128)) - (0.337633f * (U-128));
            int b = Y + (1.732446f * (U-128));

            myImage.setPixel(j, i, qRgb(r, g, b));
        }
    }

    imageLabel->setPixmap(QPixmap::fromImage(myImage));
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    //qDebug() << "Time taken by function: " << duration.count() << " milliseconds";
    //qDebug() << "End of frame at: " << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() << " milliseconds";
    delete yuvData;
}

void MainWindow::playAudio(char* data, int sz)
{
    QMediaPlayer *pAudioPlayer = new QMediaPlayer;
    QBuffer *buffer = new QBuffer(pAudioPlayer);
    buffer->setData(data, sz);
    delete data;
    buffer->open(QIODevice::ReadOnly);
    pAudioPlayer->setMedia(QMediaContent(), buffer);
    pAudioPlayer->play();
}
