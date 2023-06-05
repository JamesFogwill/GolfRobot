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
    // Opens the serial port
    STMBoard.openSerialPort();
    usleep(100000);// delay to make sure serial port is open

    // mask to allow serial communications to send
    //imshow("mask to start",Mat(100,100,CV_8UC3,Scalar(0,0,0)));
    //waitKey(10);


    int counter = 0;
    Mat Frame;
    // set the defult camera as a video capture object called inputStream.
    VideoCapture inputStream(0);
    array<int, 2> Boundaries;
    int maxSteps = 1230;
    int currentStep = 0;

    while(true){
        // displays the start menu and gets the choice from the user
        myGui.displayStart();
        int choice = myGui.getUserInput();

        if(choice == 1){

            STMBoard.writeData(to_string(choice));


        }
        else if(choice == 2){

            STMBoard.writeData(to_string(choice));
        }
        //set the boundaries
        else if(choice == 4){

            int boundariesSet = 0;
            // while the boundaries are not set
            while (boundariesSet == 0){

                // reads the current input stream and saves the frame to 'Frame'
                inputStream.read(Frame);
                // green is not accurately read to the camera within the first few frames
                // the counter is here to make sure the green is accurately read before the boundaries are set
                if(counter >= 25){

                    // detects the green and makes a Mat showing the green in a binary image
                    Mat greenDetected = myDetector.greenDetect(Frame);
                    //imshow("TheGreen", greenDetected);
                    // gets the top and bottom boundaries of the green
                    Boundaries = myDetector.boundaryDetect(greenDetected);

                    // checks the ball is within the boundaries
                    if(Boundaries[0] != 0 && Boundaries[1] != 0){
                        // prints the boundaries
                        for(int i = 0; i<2;i++){

                            cout<<"Boundary "<<i<<" is: "<<Boundaries[i]<<endl;
                            boundariesSet = 1;

                        }
                    }
                }
                counter++;

                // displays the current frame
                imshow("CameraFeed", Frame);
                waitKey(10);
            }

        }
        // option 3 is neverMiss, ball tracking software
        else if(choice == 3){
            // circle will be drawn on frame for ball tracking
            int circleRadius = 20;
            // calculate the range between the boundaries
            int rangeB = Boundaries[1] - Boundaries[0];

            // writes the choice to the STM board
            STMBoard.writeData(to_string(choice));

            while(true){

                // reads the current input stream and saves the frame to 'Frame'
                inputStream.read(Frame);
                // sets the frame size to a low resolution to match the camera and keep fps high
                resize(Frame,Frame,Size(640,480));
                // makes a binary frame where white = 1 and everything else = 0
                Mat ballDetected = myDetector.detectBall(Frame);
                imshow("Ball Detect", ballDetected);

                // stores the moments of the ball in 'm'
                Moments m = moments(ballDetected, true);
                // if the ball is detected/ if there is white on the frame to take the moment
                // m.m00 is the area of the detected object
                if(m.m00 > 0){

                    //The m.m10 and m.m01 moments represent the first-order spatial moments of the object
                    // they are used to calculate the center of the moments
                    // p(x,y) which is the centroid
                    Point p(m.m10/m.m00, m.m01/m.m00);
                    // draws a circle on mat frame with these parameters at point p
                    circle(Frame,p ,circleRadius, Scalar(255,100,100),2);
                    // make points 25 away from centroid in x and y
                    Point lineTopX(p.x + 25,p.y);
                    Point lineBotX(p.x -25,p.y);
                    Point lineTopY(p.x,p.y + 25);
                    Point lineBotY(p.x,p.y - 25);
                    // draw lines from point to point
                    line(Frame,lineTopX, lineBotX, Scalar(255,100,100),2);// line a
                    line(Frame,lineTopY, lineBotY, Scalar(255,100,100),2);// line b

                    // if the center of the ball is within the boundaries
                    if(p.y <= Boundaries[1] && p.y >= Boundaries[0]){

                        // calculate distance to the ball from the lower boundary
                        int distToBall = p.y - Boundaries[0];
                        // calc the fraction of the way the ball is across the boundaries
                        float fractionToBall = (float)distToBall/rangeB;
                        // calc the step the motor should be on to catch the ball.
                        int step = round(fractionToBall*maxSteps);
                        // checks the step is under the max
                        if(step < maxSteps){
                            // checks the step is not the same as the last step
                            if (step != currentStep){

                                cout<<"Ball is at step: "<<step<<endl;
                                // Converts p.y the int to a string of ints to be sent
                                //sends the current step through the com port
                                STMBoard.writeData(to_string(step));
                            }

                        }
                        // tells the user if there is an error, this should never happen
                        else{
                            cout<<"Critical calculation error"<<endl;
                        }
                        // updates step
                        currentStep = step;
                    }
                    // notifies user the ball has left the green
                    else{
                        cout<<"Ball Out of Bounds"<<endl;
                    }
                }
                // displays the current frame
                imshow("CameraFeed", Frame);
                waitKey(10);

            }
        }
    }
    return 0;
}
