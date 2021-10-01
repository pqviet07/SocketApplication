#ifndef SERIALIZATION_H
#define SERIALIZATION_H

char *serialize(char *buffer, int value);
char *serialize(char *buffer, unsigned int value);
char *serialize(char *buffer, unsigned short value);
char *serialize(char *buffer, char value);
char *serialize(char *buffer, char *value, int len);

#endif