#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

// Function to take the Dilated Canny edges and find the contours, then draw them on the camera feed
void getContours(Mat imgDil, Mat Frame){

    //a vector of vectors that stores the detected contours as points
    vector<vector<Point>> contours;

    // retr external retreives the external contours (contours that form object boundarys
    findContours(imgDil, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);



    /*
    //------Method by removing other contours of low area----------
    for (int i = 0; i < contours.size(); i++){
        int area = contourArea(contours[i]);
        cout<<area<<endl;
        if (area > 500){
            drawContours(Frame, contours, -1, Scalar(255,0,255), 10);
        }
    }
*/

}

int main()
{
    VideoCapture inputStream(0); // set the defult camera as a video capture object called inputStream.

    //HLS White Bounds (H,L,S)
    //Make a range detection script/ find one
    Vec3b whiteLower(0,160,0);
    Vec3b whiteUpper(255,255,255);

    //HSV Bounds


    //Vec3b lBHSV(100,100,100);
    //Vec3b uBHSV(140, 255,255);

    Mat filteredFrame;

    int circleRadius = 20;

    while(true){

        Mat Frame;

        // checks if the camera has loaded, reports error if camera cannot be opened.
        //THIS DOES NOT WORK. IF THE CAMERA IS NOT PLUGGED IN.
        if(!inputStream.isOpened()){

            cout<<"The camera did not load"<<endl;

            return -1;
        }

        // reads the current input stream and saves the frame to 'Frame'
        inputStream.read(Frame);

        //HSL colour space white tracking
        Mat HLScolourSpace;
        Mat Blurred;
        Mat Erode;
        Mat Dilate;
        //Kernal groups pixels together.
        int kernalSize = 3;
        Mat kernal = getStructuringElement(MORPH_RECT, Size(kernalSize, kernalSize));
        Point kernalAnchor = Point(-1,-1);

        //If we are using erode and dilate i think gaussian blur is detrimental here as it will group pixels together.
        //GaussianBlur(Frame,Blurred, Size(11,11), 0);

        cvtColor(Frame, HLScolourSpace, COLOR_BGR2HLS_FULL);
        inRange(HLScolourSpace,whiteLower, whiteUpper, filteredFrame);

        //the kernal anchor is the point where the operations are processed from, -1-1 is the default center of the kernal.
        // the 2 after is the number of iterations i want to run of that process.
        erode(filteredFrame, Erode, kernal, kernalAnchor, 3);
        dilate(Erode, Dilate, kernal, kernalAnchor, 2);
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
        }



        /*------------------could work?

    */


       // getContours(Dilate, Frame);

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

    cout << "Hello World!" << endl;
    return 0;
}
