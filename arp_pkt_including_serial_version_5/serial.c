#include "serial.h"
#include <windows.h>
#include <stdio.h>

// Rest of the code...


HANDLE openSerialPort(const char* portName) {
    return CreateFile(portName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
}

int configureSerialPort(HANDLE hSerial) {
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};

    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        fprintf(stderr, "Error getting serial port state\n");
        return 0;
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        fprintf(stderr, "Error setting serial port state\n");
        return 0;
    }

    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hSerial, &timeouts)) {
        fprintf(stderr, "Error setting timeouts\n");
        return 0;
    }

    return 1;
}

int sendData(HANDLE hSerial, const char* data) {
    DWORD bytesWritten;
    if (!WriteFile(hSerial, data, strlen(data), &bytesWritten, NULL)) {
        fprintf(stderr, "Error writing to serial port\n");
        return 0;
    }
    else {
        printf("Sent data successfully\n");
        return 1;
    }
}

int receiveData(HANDLE hSerial, char* buffer, DWORD bufferSize) {
    DWORD bytesRead;
    if (!ReadFile(hSerial, buffer, bufferSize, &bytesRead, NULL)) {
        fprintf(stderr, "Error reading from serial port\n");
        return 0;
    }
    buffer[bytesRead] = '\0';
    printf("Received: %s\n", buffer);
    return 1;
}

void closeSerialPort(HANDLE hSerial) {
    CloseHandle(hSerial);
}
