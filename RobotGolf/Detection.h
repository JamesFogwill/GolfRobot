#ifndef DETECTION_H
#define DETECTION_H
#include <setup.h>

class Detector{

private:

    // HSV BOUNDS white
    Vec3b whiteLowerHsv = Vec3b(0,0,230);
    Vec3b whiteUpperHsv = Vec3b(55,60,255);

    //HSV GREEN BOUNDS
    Vec3b greenLowerHsv = Vec3b(35,0,20);
    Vec3b greenUpperHsv = Vec3b(90,255,255);

    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));





protected:
public:


    Mat detectBall(Mat);

    Mat greenDetect(Mat);

    array<int,2>boundaryDetect(Mat);




};

#endif // DETECTION_H
