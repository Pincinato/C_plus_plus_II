#ifndef EYEANALYSER_H
#define EYEANALYSER_H


#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
using namespace cv;
using namespace std;

class EyeAnalyser
{
public:
    EyeAnalyser();
    short getEyePosition(const Mat &frame,const deque<Point> &leftEye,const deque<Point> &rightEye);
    short getDirection(const Mat &frame,const Point &calibrationLeft,const Point &calibrationRight,const deque<Point> &leftEye,const deque<Point> &rightEye);
    float getSumPixel(const Mat &image);
    bool LeftRight(float leftValue,float rightValue);
    bool UpDown(float upValue, float downValue);
    short getDistance(const Point &calibration,const deque<Point> &Eye);

private:
    Point averagePoint(const deque<Point> &vec);
    int sensibility;

};

#endif // EYEANALYSER_H
