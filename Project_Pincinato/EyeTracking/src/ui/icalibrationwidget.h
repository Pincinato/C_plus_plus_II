#ifndef ICALIBRATIONWIDGET_H
#define ICALIBRATIONWIDGET_H

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

/*!
 * \brief The ICalibrationWidget class
 */
class ICalibrationWidget {
public:
    /*!
     * \brief ICalibrationWidget
     */
    ICalibrationWidget(){}

    /*!
     * \brief ~ICalibrationWidget
     */
    virtual ~ICalibrationWidget(){}

    /*!
     * \brief setCalibrationPoint
     * \param eyeLeft
     * \param eyeRight
     */
    virtual void setCalibrationPoint(const cv::Point &eyeLeft,const cv::Point &eyeRight) =0;

};


#endif // ICALIBRATIONWIDGET_H
