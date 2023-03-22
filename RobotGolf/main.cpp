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

    vector<vector<Point>> contours;
    vector<Vec4i> heirarchy;

    findContours(imgDil, contours, heirarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    drawContours(Frame, contours, -1, Scalar(255,0,255), 10);
}

int main()
{
    VideoCapture inputStream(0); // set the defult camera as a video capture object called inputStream.
    Vec3b uBHSV(255,30,255);
    Vec3b lBHSV(0,0,200);

    //Vec3b lBHSV(100,100,100);
    //Vec3b uBHSV(140, 255,255);

    Mat filteredFrame;

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


        /*//HSV colour space White tracking
        Mat HSVcolourSpace;
        cvtColor(Frame, HSVcolourSpace, COLOR_BGR2HSV_FULL);
        inRange(HSVcolourSpace, lBHSV, uBHSV, filteredFrame);
        imshow("Filtered Frame", filteredFrame);
        */

        // using canny edge detection and contours to locate the golfball.
        Mat cSGray, gBlur, cannyED, dil;
        cvtColor(Frame, cSGray, COLOR_BGR2GRAY);
        GaussianBlur(cSGray,gBlur, Size(3,3),3,0); // Try more gaussian blur to remove background edges.
        Canny(gBlur,cannyED,75, 150);
        Mat kernal = getStructuringElement(MORPH_RECT, Size(3,3));
        dilate(cannyED,dil,kernal);

        getContours(dil,Frame);

        imshow("gray", cSGray);
        imshow("gaussian blur", gBlur);
        imshow("Canny", cannyED);
        imshow("dilate", dil);

        // displays the current frame
        imshow("CameraFeed", Frame);
        waitKey(10);

    }

    cout << "Hello World!" << endl;
    return 0;
}
