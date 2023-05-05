#ifndef SERIALPORTCLASS_H
#define SERIALPORTCLASS_H
#include <setup.h>

class SerialCommunicator
{
    private:

        QSerialPort *STM;

        // IDs to check the board connected is the correct one.
        // Also a way to know if im interfacing with the right port.
        static const quint16 STMVendorID = 1155;
        static const quint16 STMProductID = 14155;

        QString STMPortName = "";
        bool STMAvailable;


    protected:

    public:

        SerialCommunicator();

        void openSerialPort();

        void writeData(string data);

};

#endif // SERIALPORTCLASS_H
