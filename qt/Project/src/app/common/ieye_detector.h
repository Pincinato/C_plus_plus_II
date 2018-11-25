#ifndef IEYE_DETECTOR_H
#define IEYE_DETECTOR_H

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <thread>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

class Ieye_detector{
public:
    Ieye_detector(){}
    virtual ~Ieye_detector(){}
    virtual void setData(Mat &frame)=0;
    virtual void setStatus(string cameraStatus)=0;
};
#endif // IEYE_DETECTOR_H
