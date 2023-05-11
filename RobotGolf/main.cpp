#include <setup.h>
#include <SerialPortClass.h>
#include <BufferClass.h>
#include <GuiClass.h>
#include<unistd.h>
#include <QCoreApplication>
#include <Detection.h>

Gui myGui;
SerialCommunicator STMBoard;
Detector myDetector;

int main(int argc, char *argv[])
{
    //QCoreApplication app(argc, argv);

    int choice = myGui.getUserInput();
    STMBoard.openSerialPort();
    usleep(100000);
    // mask to allow serial communications to send
    imshow("mask to start",Mat(100,100,CV_8UC3,Scalar(0,0,0)));
    STMBoard.writeData(to_string(choice));

    if(choice == 3){

        Mat Frame;
        VideoCapture inputStream(0); // set the defult camera as a video capture object called inputStream.

        int circleRadius = 20;
        int boundariesSet = 0;

        while(true){

            // reads the current input stream and saves the frame to 'Frame'
            inputStream.read(Frame);

            if(boundariesSet == 0){
                Mat greenDetected = myDetector.greenDetect(Frame);
                imshow("TheGreen", greenDetected);

                array<int, 2> Boundaries = myDetector.boundaryDetect(greenDetected);

                for(int i = 0; i<2;i++){

                    STMBoard.writeData(to_string(Boundaries[i]));
                    cout<<"Boundary "<<i<<" is: "<<Boundaries[i]<<endl;
                    boundariesSet = 1;

                }
            }

            Mat greenDetected = myDetector.greenDetect(Frame);
            imshow("TheGreen", greenDetected);

            Mat ballDetected = myDetector.detectBall(Frame);
            imshow("Ball Detect", ballDetected);

            Moments m = moments(ballDetected, true);
            if(m.m00 > 0){

                Point p(m.m10/m.m00, m.m01/m.m00);
                circle(Frame,p ,circleRadius, Scalar(255,100,100),2);

                Point lineTopX(p.x + 25,p.y);
                Point lineBotX(p.x -25,p.y);
                Point lineTopY(p.x,p.y + 25);
                Point lineBotY(p.x,p.y - 25);
                line(Frame,lineTopX, lineBotX, Scalar(255,100,100),2);// line a
                line(Frame,lineTopY, lineBotY, Scalar(255,100,100),2);// line b

                // Converts p.y the int to a string of ints to be sent
                //send p.y through the com port
                //cout<<p.y<<endl;

                STMBoard.writeData(to_string(p.y));
            }


            // displays the current frame
            imshow("CameraFeed", Frame);
            waitKey(10);

        }
    }
    //return app.exec();
    return 0;
}
