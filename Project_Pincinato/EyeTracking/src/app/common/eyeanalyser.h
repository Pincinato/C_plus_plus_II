#ifndef EYEANALYSER_H
#define EYEANALYSER_H


#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <deque>
using namespace cv;
using namespace std;

class EyeAnalyser
{
public:
    EyeAnalyser();
    short getDirection(const Point &calibrationLeft,const Point &calibrationRight,const deque<Point> &leftEye,const deque<Point> &rightEye);
    short getDistance(const Point &calibration,const deque<Point> &Eye);
    void setSensibility(int newValue);

private:
    Point medianPoint(const deque<Point> &input);
    int sensibility;
    deque<int> m_valueX;
    deque<int> m_valueY;
    std::vector<cv::Point> m_centers;

};

#endif // EYEANALYSER_H
