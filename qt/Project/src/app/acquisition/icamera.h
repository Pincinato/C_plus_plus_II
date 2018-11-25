#ifndef ICAMERA_H
#define ICAMERA_H

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <thread>
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

class Icamera
{
public:
    Icamera(){}
    virtual ~Icamera(){}
    virtual void setData(Mat &frame)=0;
    virtual void setStatus(string cameraStatus)=0;

};

#endif // ICAMERA_H
