 #include "WAV_Reader.h"

int main()
{
    // test: split WAV file
    WAV_Reader wav("/home/quocviet/Desktop/SocketApplication/raw_audio.wav");
    wav.showHeaderInfo();
    
    wav.splitWavData(3);

    return 0;
}