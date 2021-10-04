#include "serialization.h"
#include <iostream>

char *serialize(char *buffer, int value)
{
    buffer[0] = value >> 24;
    buffer[1] = value >> 16;
    buffer[2] = value >> 8;
    buffer[3] = value;
    return buffer + 4;
}

char *serialize(char *buffer, unsigned int value)
{
    buffer[0] = value >> 24;
    buffer[1] = value >> 16;
    buffer[2] = value >> 8;
    buffer[3] = value;
    return buffer + 4;
}

char *serialize(char *buffer, unsigned short value)
{
    buffer[0] = value >> 16;
    buffer[1] = value >> 8;
    return buffer + 2;
}

char *serialize(char *buffer, char value)
{
    buffer[0] = value;
    return buffer + 1;
}

char *serialize(char *buffer, char *value, int len)
{
    for (int i = 0; i < len; i++) 
    {
        buffer[i] = value[i];
        std::cout << buffer[i] <<" ";
    }
    return buffer + 1;
}