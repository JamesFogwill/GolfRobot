#include <Detection.h>

Mat Detector::detectBall(Mat Frame){

    Mat HSVColourSpace;
    Mat whiteShow;

    cvtColor(Frame,HSVColourSpace, COLOR_BGR2HSV);
    inRange(HSVColourSpace,whiteLowerHsv,whiteUpperHsv, whiteShow);

    erode(whiteShow, whiteShow, kernel);
    dilate(whiteShow, whiteShow, kernel);

    dilate(whiteShow, whiteShow, kernel);
    erode(whiteShow, whiteShow, kernel);
    return whiteShow;
}

Mat Detector::greenDetect(Mat Frame){

    Mat greenShow;
    Mat HSVColourSpace;

    cvtColor(Frame,HSVColourSpace, COLOR_BGR2HSV);
    inRange(HSVColourSpace,greenLowerHsv,greenUpperHsv, greenShow);
    erode(greenShow, greenShow, kernel);
    dilate(greenShow, greenShow, kernel);

    dilate(greenShow, greenShow, kernel);
    erode(greenShow, greenShow, kernel);

    // resize to 1 pixel width so the height is all on the same y pixel
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
        // loops through the height anc checks when the pixel values changes to 1
        int pixelVal = maskedEdge.at<int>(i,300);
        if(pixelVal == -1){
            boundaries[0] = i;
            for(int position = i; position <=height;position++){

                int pixelVal = maskedEdge.at<int>(position,200);

                if(pixelVal == 0){
                    boundaries[1] = position;

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

