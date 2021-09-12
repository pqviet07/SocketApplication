#ifndef YUV_READER_H
#define YUV_READER_H
#include <QThread>
#include <QFile>
#include <MyWindow.h>
#include <Y4M_Reader.h>

class YUV_Render : public QThread
{
private:
    std::string *yuvData{nullptr};
    Y4M_Reader *reader{nullptr};
    MyWindow *mainWindow{nullptr};
public:
    YUV_Render(MyWindow*, Y4M_Reader*);
    std::string* readNextFrame();
    void run() override;
};

#endif // YUV_READER_H
