#include "mbed.h"
#include "stdio.h"
#include <cstdio>
#include <string>
#include "iostream"
#include "cstdlib"


class SerialClass {

    private:

    // init the bufferd serial
    BufferedSerial pc;
    // init the string to store the data
    string data;

    int bufferIdx = 0;
    // character to hold the read characters
    char c;

    int serialInt;

    protected:

    public:

    // constructor
    SerialClass();

    int serialRead();

    void serialWrite(int, int);

};