#include "SetUp.h"


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
            
            // if the data is a 's'
            // 'character' "string"
            if(c != 's'){
                continue;
            }
            data.clear();
            while(1)
            {
                if (pc.readable()) {
                    pc.read(&c, 1);
                    if(c=='e')
                    {
                        break;
                    }
                    data += c;
                }
            }
            serialInt = atoi(data.c_str());
            //pc.write(data.c_str(),3);
            return serialInt;
        }
    }
}

void SerialClass::serialWrite(int data){

    sprintf(outputBuffer, "%d", data);
    pc.write(outputBuffer,strlen(outputBuffer));

}