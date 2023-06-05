#include <Detection.h>

Mat Detector::detectBall(Mat Frame){

    Mat HSVColourSpace;
    Mat whiteShow;
    // convert frame to hsv colour space and check between the white bounds, display anything between the bounds
    cvtColor(Frame,HSVColourSpace, COLOR_BGR2HSV);
    inRange(HSVColourSpace,whiteLowerHsv,whiteUpperHsv, whiteShow);
    // morphology processes to remove background noise in the image
    erode(whiteShow, whiteShow, kernel);
    dilate(whiteShow, whiteShow, kernel);

    dilate(whiteShow, whiteShow, kernel);
    erode(whiteShow, whiteShow, kernel);
    return whiteShow;
}

Mat Detector::greenDetect(Mat Frame){

    Mat greenShow;
    Mat HSVColourSpace;
    // convert to hsv colour space, check between green bounds, display anything betwen the bounds
    cvtColor(Frame,HSVColourSpace, COLOR_BGR2HSV);
    inRange(HSVColourSpace,greenLowerHsv,greenUpperHsv, greenShow);
    erode(greenShow, greenShow, kernel);
    dilate(greenShow, greenShow, kernel);

    dilate(greenShow, greenShow, kernel);
    erode(greenShow, greenShow, kernel);

    // resize to 1 pixel width and then brings back out to the normal size, this takes a average for the boundaries
    Mat maskEdge;
    resize(greenShow,maskEdge,Size(1,greenShow.size().height));
    resize(maskEdge,maskEdge,greenShow.size());

    imshow("greenDetect",greenShow);
    imshow("HSV",HSVColourSpace);
    imshow("theGreen", maskEdge);
    return maskEdge;

}

array<int,2> Detector::boundaryDetect(Mat maskedEdge){
    // sets boundaries array and the height of the frame
    int height = maskedEdge.rows;
    array<int, 2>boundaries;
    for(int i = 0; i <= height; i ++){
        // loops through the height anc checks when the pixel values changes to -1
        int pixelVal = maskedEdge.at<int>(i,300);
        // -1 is the value of the white, where the green starts
        if(pixelVal == -1){
            // store the coordinate where it changes in the boundaries array
            boundaries[0] = i;
            for(int position = i; position <=height;position++){
                // continues looping from the lower boundary to find the upper boundary

                int pixelVal = maskedEdge.at<int>(position,300);
                // when the green ends store that pixel as the upper boundary
                if(pixelVal == 0){
                    boundaries[1] = position;
                    // check to make sure the boundarys are sensible numbers (between the resolution)
                    if(boundaries[0] >= 2 && boundaries[0] <= 478 && boundaries[1] >= 2 && boundaries[1] <=478){
                        return boundaries;
                        cout<<"collect boundaries success"<<endl;
                    }
                    else
                        break;
                }
            }
            break;
        }
    }


    cout<<"collect boundaries failed"<<endl;
    return boundaries ={0};


}

