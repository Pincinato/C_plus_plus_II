#ifndef ICALIBRATIONWIDGET_H
#define ICALIBRATIONWIDGET_H

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

/*!
 * \brief The ICalibrationWidget class  inteface Classe for CalibrationWidget
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
     * \brief setCalibrationPoint       virtual method
     * \param eyeLeft                   Point at the center of left eye
     * \param eyeRight                  Point at the center of right eye
     */
    virtual void setCalibrationPoint(const cv::Point &eyeLeft,const cv::Point &eyeRight) =0;

};


#endif // ICALIBRATIONWIDGET_H
