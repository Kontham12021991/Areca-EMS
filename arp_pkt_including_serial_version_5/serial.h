#ifndef SERIAL_H
#define SERIAL_H

#include <windows.h>
#include <stdio.h>

#define BUFFER_SIZE 256

// Function declarations
HANDLE openSerialPort(const char* portName);
int configureSerialPort(HANDLE hSerial);
int sendData(HANDLE hSerial, const char* data);
int receiveData(HANDLE hSerial, char* buffer, DWORD bufferSize);
void closeSerialPort(HANDLE hSerial);

#endif /* SERIAL_H */
