#include <setup.h>
#include <SerialPortClass.h>
#include <BufferClass.h>
#include <GuiClass.h>
#include<unistd.h>
#include <QCoreApplication>

Gui myGui;
SerialCommunicator STMBoard;

int main(int argc, char *argv[])
{
    //QCoreApplication app(argc, argv);

    int choice = myGui.getUserInput();
    STMBoard.openSerialPort();
    usleep(100000);

    imshow("Inrange",Mat(100,100,CV_8UC3,Scalar(0,0,0)));
    STMBoard.writeData(to_string(choice));

//    while(1)
//    {
//        usleep(10000);
//        STMBoard.writeData(to_string(choice));
//    }




    if(choice == 3){

        VideoCapture inputStream(0); // set the defult camera as a video capture object called inputStream.

        //HLS White Bounds (H,L,S)
        //Make a range detection script/ find one
        Vec3b whiteLower(0,160,0);
        Vec3b whiteUpper(255,255,255);

        // HSV BOUNDS
        Vec3b whiteLowerHsv(0,0,210);
        Vec3b whiteUpperHsv(255,75,255);

        Mat filteredFrame;

        int circleRadius = 20;

        //yCoordinate.setNum(testData);
        //STMBoard.writeData(yCoordinate);

        while(true){

            Mat Frame;

            // reads the current input stream and saves the frame to 'Frame'
            inputStream.read(Frame);

            //HSL colour space white tracking
            Mat HLScolourSpace;
            Mat HSVColourSpace;
            Mat Blurred;
            Mat outputFrame;
            Mat Erode;
            Mat Dilate;
            //Kernal groups pixels together.
            int kernalSize = 5;
            Mat kernal = getStructuringElement(MORPH_RECT, Size(kernalSize, kernalSize));
            Point kernalAnchor = Point(-1,-1);


            //If we are using erode and dilate i think gaussian blur is detrimental here as it will group pixels together.
            //GaussianBlur(Frame,Blurred, Size(11,11), 0);

            cvtColor(Frame, HLScolourSpace, COLOR_BGR2HLS);
            cvtColor(Frame,HSVColourSpace, COLOR_BGR2HSV);

            inRange(HSVColourSpace,whiteLowerHsv,whiteUpperHsv, filteredFrame);
            imshow("Inrange",filteredFrame );

            //the kernal anchor is the point where the operations are processed from, -1-1 is the default center of the kernal.
            // the 2 after is the number of iterations i want to run of that process.
            morphologyEx(filteredFrame,Dilate,MORPH_CLOSE,kernal);
            imshow("HLS",Dilate);


            Moments m = moments(Dilate, true);
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
            /*
            //HSV colour space White tracking
            Mat HSVcolourSpace;
            cvtColor(Frame, HSVcolourSpace, COLOR_BGR2HSV_FULL);
            inRange(HSVcolourSpace, whiteLower, whiteUpper, filteredFrame);
            imshow("Filtered Frame", filteredFrame);
            */

            // displays the current frame
            imshow("CameraFeed", Frame);
            waitKey(10);

        }
    }
    //return app.exec();
    return 0;
}
