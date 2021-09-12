#include <MyWindow.h>
#include <QPushButton>
MyWindow::MyWindow()
{
    QWidget *window = new QWidget;
    window->setGeometry(100,100,800,600);
    QVBoxLayout* layout= new QVBoxLayout;
    imageLabel=new QLabel;
    layout->addWidget(imageLabel);
    window->setLayout(layout);
    window->show();
}
void MyWindow::render(const QByteArray yuvData, int width, int height)
{
    QImage *myImage= new QImage(width, height, QImage::Format_ARGB32);

    for(int i=0; i<height; i++)
    {
        for(int j=0;j<width; j++)
        {
            int Y = 0xFF & yuvData[(i * width) + j];
            int dx = ((i / 2) * (width / 2)) + (j / 2);
            int U = 0xFF & yuvData[width*height + dx];
            int V = 0xFF & yuvData[width*height+width*height/4 + dx];

            int r = Y + (1.370705f * (V-128));
            int g = Y - (0.698001f * (V-128)) - (0.337633f * (U-128));
            int b = Y + (1.732446f * (U-128));

            myImage->setPixel(j, i, qRgb(r, g, b));
        }
    }

    imageLabel->setPixmap(QPixmap::fromImage(*myImage));
}
