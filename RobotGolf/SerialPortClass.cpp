#include <SerialPortClass.h>
#include <setup.h>

SerialCommunicator::SerialCommunicator(){
    STM = new QSerialPort;
    qDebug() << "Number of available serial ports: "<<QSerialPortInfo::availablePorts().length()<<Qt::endl;

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        if(serialPortInfo.vendorIdentifier() == STMVendorID && serialPortInfo.productIdentifier() == STMProductID){
            STMPortName = serialPortInfo.portName();// this gets the port name of the stm board so i can use different com ports. it will always be detected.
            STMAvailable = true;
            cout << "STM board is detected" <<endl;
        }
    }

    if(STMAvailable == true){
        STM->setPortName(STMPortName);
        STM->open(QSerialPort::WriteOnly);
        STM->setBaudRate(QSerialPort::Baud9600);
        STM->setDataBits(QSerialPort::Data8);
        STM->setParity(QSerialPort::NoParity);
        STM->setStopBits(QSerialPort::OneStop);
        STM->setFlowControl(QSerialPort::NoFlowControl);
        cout<<"STM communication is open."<<endl;
    }
    else{
        cout<<"Cannot open STM serial communication."<<endl;
    }
}

void SerialCommunicator::openSerialPort()
{


 }

void SerialCommunicator::writeData(string data){

    data="s"+data+"e";
    cout<<data<<endl;
    if(STM->isWritable()){
        STM->write(data.c_str());
        cout<<data<<endl;
    }
    else{
        cout<<"Could not write to STM board"<<endl;
    }
}

