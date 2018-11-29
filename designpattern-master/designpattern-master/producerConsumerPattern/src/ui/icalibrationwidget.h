#ifndef ICALIBRATIONWIDGET_H
#define ICALIBRATIONWIDGET_H

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class ICalibrationWidget {
public:
    ICalibrationWidget(){}
    virtual ~ICalibrationWidget(){}
    virtual void setCalibrationPoint(const cv::Point eye_center) =0;

};


#endif // ICALIBRATIONWIDGET_H