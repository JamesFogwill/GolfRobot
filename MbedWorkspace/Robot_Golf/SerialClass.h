#include "mbed.h"
#include "stdio.h"
#include <cstdio>
#include <string>
#include "iostream"
#include "cstdlib"


class SerialClass {

    private:

    BufferedSerial pc;

    char outputBuffer[10] = {0};

    string data;

    int bufferIdx = 0;

    char c;

    bool storeData = false;

    int serialInt;

    protected:

    public:

    // constructor
    SerialClass();

    int serialRead();

    void serialWrite(int data);

};