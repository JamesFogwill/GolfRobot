
/*

// Function to take the Dilated Canny edges and find the contours, then draw them on the camera feed
void getContours(Mat imgDil, Mat Frame){

    //a vector of vectors that stores the detected contours as points
    vector<vector<Point>> contours;

    // retr external retreives the external contours (contours that form object boundarys
    findContours(imgDil, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);




    //------Method by removing other contours of low area----------
    for (int i = 0; i < contours.size(); i++){
        int area = contourArea(contours[i]);
        cout<<area<<endl;
        if (area > 500){
            drawContours(Frame, contours, -1, Scalar(255,0,255), 10);
        }
    }


}

// Function to take the Dilated Canny edges and find the contours, then draw them on the camera feed
void getContours(Mat imgDil, Mat Frame){

    //a vector of vectors that stores the detected contours as points
    vector<vector<Point>> contours;
    vector<Vec4i> heirarchy;
    // retr external retreives the external contours (contours that form object boundarys
    findContours(imgDil, contours, heirarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    drawContours(Frame, contours, -1, Scalar(255,0,255), 10);
}
// using canny edge detection and contours to locate the golfball.
// Preproscessing of the image
Mat cSGray, gBlur, cannyED, dil;
cvtColor(Frame, cSGray, COLOR_BGR2GRAY);
GaussianBlur(cSGray,gBlur, Size(1,1),0,0); // Try more gaussian blur to remove background edges.
Canny(gBlur,cannyED,75, 150);
Mat kernal = getStructuringElement(MORPH_RECT, Size(3,3));
dilate(cannyED,dil,kernal);

getContours(dil,Frame);

imshow("gray", cSGray);
imshow("gaussian blur", gBlur);
imshow("Canny", cannyED);
imshow("dilate", dil);

*/
