#include <setup.h>
#include <BufferClass.h>


circularBuffer::circularBuffer(int size) :bufferSize(size), ballPositions(new QByteArray[size]), writeIdx(0){

}

circularBuffer::~circularBuffer() {
    delete[] ballPositions; // deallocate the memory for buffer
}

void circularBuffer::writeBuffer(int data) {
    QByteArray byteData;
    byteData.setNum(data);
    ballPositions[writeIdx] = byteData;
    writeIdx = (writeIdx + 1) % bufferSize;
}

QByteArray circularBuffer::readBuffer(){

}
