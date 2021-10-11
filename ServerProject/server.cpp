#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <errno.h>
#include <vector>
#include <thread>
#include "Y4M_Reader/Y4M_Reader.h"
#include "WAV_Reader/WAV_Reader.h"
const int DURATION = 150;

int send_data(int socket, Y4M_Reader *y4m_reader, WAV_Reader *wav_reader)
{
   long long stat;
   printf("Sending Picture as Byte Array\n");
   std::vector<std::string*> yuvFrameList;
   int duration = DURATION;
   int nCurrentByteYUV = 0;
   int curFrame = 0;
   int nByteImagePerPeriod = (duration/1000.0) * y4m_reader->getHeader()->frameSize * y4m_reader->getHeader()->fps;
   int nByteAudioPerPeriod = sizeof(WAV_Header) + duration * wav_reader->getHeader()->byteRate / 1000;
   int totalBytePerPeriod = nByteImagePerPeriod+nByteAudioPerPeriod;

   std::cout << "TotalBytePerPeriod: " << totalBytePerPeriod << std::endl;
   std::cout << "nByteImagePerPeriod: " << nByteImagePerPeriod << std::endl;
   std::cout << "nByteAudioPerPeriod: " << nByteAudioPerPeriod << std::endl;

   // send header info ------------------------------------------------
   write(socket, (char*)wav_reader->getHeader(), sizeof(WAV_Header));
   write(socket, (char*)&duration, sizeof(int));
   write(socket, (char*)&nByteAudioPerPeriod, sizeof(int));
   write(socket, (char*)&totalBytePerPeriod, sizeof(int));

   write(socket, (char*)y4m_reader->getHeader(), sizeof(Y4M_Header));
   write(socket, (char*)&duration, sizeof(int));
   write(socket, (char*)&nByteImagePerPeriod, sizeof(int));
   write(socket, (char*)&totalBytePerPeriod, sizeof(int));
   // ----------------------------------------------------------------

   // Send audio frame + video frame
   while (!wav_reader->isEOF() || !y4m_reader->isEOF())
   {
      time_t start = std::clock();

      if (!wav_reader->isEOF())
      {
         std::string *wavFrame = wav_reader->getNextFrame(duration);
         // Send data through our socket
         do
         {
            // send wav frame (1000ms)
            stat = write(socket, wavFrame->c_str(), wavFrame->size());
         } while (stat < 0);
         delete wavFrame;
      }

      if (!y4m_reader->isEOF())
      {
         while (nCurrentByteYUV + nByteImagePerPeriod > curFrame * y4m_reader->getHeader()->frameSize)
         {
            std::string *yuvFrame = y4m_reader->getNextFrame();
            yuvFrameList.push_back(yuvFrame);
            ++curFrame;
         }
         int start = nCurrentByteYUV == 0 ? 0 : (nCurrentByteYUV - 1) / y4m_reader->getHeader()->frameSize;
         int i = nCurrentByteYUV == 0 ? 0 : (nCurrentByteYUV - 1) % y4m_reader->getHeader()->frameSize;
         std::string temp;
         for (int cnt = 0; cnt < nByteImagePerPeriod; cnt++)
         {
            temp.push_back((*yuvFrameList[start])[i++]);
            if (i == y4m_reader->getHeader()->frameSize)
            {
               start++;
               i = 0;
            }
         }
         do
         {
            // send yuv frame
            stat = write(socket, temp.c_str(), temp.size());
         } while (stat < 0);
         nCurrentByteYUV += nByteImagePerPeriod;
      }

      time_t finish = std::clock();
      double latency = double(finish - start)/CLOCKS_PER_SEC;
      //std::cout << latency*1000 << " ms" << std::endl;
      int sleeptime=DURATION-latency*1000;
      if(sleeptime<0) sleeptime=0;

      std::this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
   }

   for (auto &&var : yuvFrameList) delete var;
   return 0;
}

int main(int argc, char *argv[])
{
   int socket_desc, new_socket, c, read_size, buffer = 0;
   struct sockaddr_in server, client;
   char *readin;

   //Create socket
   socket_desc = socket(AF_INET, SOCK_STREAM, 0);
   if (socket_desc == -1)
   {
      printf("Could not create socket");
   }

   //Prepare the sockaddr_in structure
   server.sin_family = AF_INET;
   server.sin_addr.s_addr = INADDR_ANY;
   server.sin_port = htons(8889);

   //Bind
   if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
   {
      puts("bind failed");
      return 1;
   }

   puts("bind done");

   //Listen
   listen(socket_desc, 3);

   //Accept and incoming connection
   puts("Waiting for incoming connections...");
   c = sizeof(struct sockaddr_in);

   if ((new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c)))
   {
      puts("Connection accepted");
   }

   fflush(stdout);

   if (new_socket < 0)
   {
      perror("Accept Failed");
      return 1;
   }

   Y4M_Reader *y4m_reader = new Y4M_Reader("raw_video.y4m");
   WAV_Reader *wav_reader = new WAV_Reader("raw_audio.wav");

   send_data(new_socket, y4m_reader, wav_reader);

   delete y4m_reader;
   delete wav_reader;

   close(socket_desc);
   fflush(stdout);
   printf("finish");
   return 0;
}