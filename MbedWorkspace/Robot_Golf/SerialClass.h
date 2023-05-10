#include "mbed.h"
#include "stdio.h"
#include <cstdio>
#include <string>
#include "iostream"
#include "cstdlib"


class SerialClass {

    private:

    BufferedSerial pc;

    string data;

    int bufferIdx = 0;

    char c;

    int serialInt;

    protected:

    public:

    // constructor
    SerialClass();

    int serialRead();

    void serialWrite(int, int);

};