#include <SerialPortClass.h>
#include <setup.h>

SerialCommunicator::SerialCommunicator(){
    // creates new serialport object and checks the number of available ports
    STM = new QSerialPort;
    qDebug() << "Number of available serial ports: "<<QSerialPortInfo::availablePorts().length()<<Qt::endl;
    // loops through the available ports and checks their vendor and product id against that of my stm board
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.vendorIdentifier() == STMVendorID && serialPortInfo.productIdentifier() == STMProductID){
            // this gets the port name of the stm board so i can use different com ports. it will always be detected.
            STMPortName = serialPortInfo.portName();
            STMAvailable = true;
            cout << "STM board is detected" <<endl;
        }
    }
}

void SerialCommunicator::openSerialPort()
{   // configures the port if its availble to do
    if(STMAvailable == true){
        // takes port name from the constructor
        STM->setPortName(STMPortName);
        STM->setBaudRate(QSerialPort::Baud9600);
        STM->setDataBits(QSerialPort::Data8);
        STM->setParity(QSerialPort::NoParity);
        STM->setStopBits(QSerialPort::OneStop);
        STM->setFlowControl(QSerialPort::NoFlowControl);
        STM->open(QSerialPort::WriteOnly);
        // checks to make sure the port is open as it can take some delay sometimes.
        if(STM->isOpen()){
            cout<<"STM communication is open."<<endl;
        }
        else{
            cout<<"failed to open port"<<endl;
        }
    }
    else{
        cout<<"Cannot open STM serial communication."<<endl;
    }
 }

void SerialCommunicator::writeData(string data){
    // concatinates a s and e onto the data as special characters that mbed can read
    data="s"+data+"e";
    // if stm is writeable, write the data
    if(STM->isWritable()){
        STM->write(data.c_str());
        cout<<data<<endl;
    }
    else{
        cout<<"Could not write to STM board"<<endl;
    }
    // wait key because its like an update function.
    waitKey(10);
}

