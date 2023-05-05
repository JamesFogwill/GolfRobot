#ifndef BUFFERCLASS_H
#define BUFFERCLASS_H
#include <setup.h>

class circularBuffer {

private:

    //initialises buffer and makes all values = 0
    QByteArray* ballPositions;
    int bufferSize;
    int writeIdx;
    int readIdx;

protected:

public:

    circularBuffer(int size);
    ~circularBuffer();


    void writeBuffer(int data);

    QByteArray readBuffer();
    //write a function to read the first from the buffer and i should be able to put that into the stm.write
};
#endif // BUFFERCLASS_H
