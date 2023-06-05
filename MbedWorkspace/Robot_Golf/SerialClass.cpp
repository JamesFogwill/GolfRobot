#include "SetUp.h"
#include <string>


SerialClass::SerialClass() : pc(USBTX,USBRX){

// constructor
    pc.set_baud(9600);

}

int SerialClass::serialRead(){

    while(true){
        // if the port is readable
        if (pc.readable()) {
            // read the data
            pc.read(&c, 1);
            // if the data is not an 's' continue to check
            // 'character' "string"
            if(c != 's'){
                continue;
            }
            // clear the buffer when data is incoming
            data.clear();
            while(1)
            {
                // check readable then read until an 'e' is recieved
                if (pc.readable()) {
                    pc.read(&c, 1);
                    if(c=='e')
                    {
                        break;
                    }
                    // store eachh character into the data string
                    data += c;
                }
            }
            // convert the string to an int
            serialInt = atoi(data.c_str());
            // echo the data back
            pc.write(data.c_str(),3);
            return serialInt;
        }
    }
}
// function to send data back to qt, can specify the size of the data you want to send in characters
void SerialClass::serialWrite(int data, int size){
    // convert int data to string and then write the data to qt 
    string dataStr = to_string(data);
    pc.write(dataStr.c_str(),size);

}