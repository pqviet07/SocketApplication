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

using namespace std;
int send_data(int socket, Y4M_Reader *y4m_reader, WAV_Reader *wav_reader)
{
   long long stat;
   printf("Sending Picture as Byte Array\n");
   std::vector<std::string*> yuvFrameList;
   int duration = 1000;
   int nCurrentByteYUV = 0;
   int curFrame = 0;
   int nBytePerPeriod = (duration/1000.0) * y4m_reader->getFrameSize() * y4m_reader->getHeader().fps;

   while (true)
   {
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
         while (nCurrentByteYUV + nBytePerPeriod > curFrame * y4m_reader->getFrameSize())
         {
            std::string *yuvFrame = y4m_reader->getNextFrame();
            yuvFrameList.push_back(yuvFrame);
            ++curFrame;
         }
         int start = nCurrentByteYUV == 0 ? 0 : (nCurrentByteYUV - 1) / y4m_reader->getFrameSize();
         int i = nCurrentByteYUV == 0 ? 0 : (nCurrentByteYUV - 1) % y4m_reader->getFrameSize();
         std::string temp;
         for (int cnt = 0; cnt < nBytePerPeriod; cnt++)
         {
            temp.push_back((*yuvFrameList[start])[i++]);
            if (i == y4m_reader->getFrameSize())
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
         nCurrentByteYUV += nBytePerPeriod;
      }

      if (wav_reader->isEOF() && y4m_reader->isEOF()) break;
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