#ifndef ICALIBRATIONWIDGET_H
#define ICALIBRATIONWIDGET_H

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class ICalibrationWidget {
public:
    ICalibrationWidget(){}
    virtual ~ICalibrationWidget(){}
    virtual void setCalibrationPoint(const cv::Mat &frame,const cv::Point &eyeLeft,const cv::Point &eyeRight) =0;

};


#endif // ICALIBRATIONWIDGET_H
