#ifndef Y4M_HEADER_H
#define Y4M_HEADER_H
#pragma pack(1)  
struct Y4M_Header
{
    char signature[10];
    int width;
    int height;
    int fps;
    char interlacing_mode;
    char pixel_ratio[5];
    char color_space[8];
};

#endif