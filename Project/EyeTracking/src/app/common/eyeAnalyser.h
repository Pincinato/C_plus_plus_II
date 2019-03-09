/****************************************************************************
** Copyright (c) 2018 University of Bern & Bern University of Applied Science
** Project: Eye tracking
**
** Contact:  Thiago Henrique Pincianto ( thiago.pincinato@bfh.ch )
*****************************************************************************/
#ifndef EYEANALYSER_H
#define EYEANALYSER_H


#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#include <deque>
using namespace cv;
using namespace std;
/*!
 * \brief The EyeAnalyser class     Resposible to analyse the result of eyes center and
 *                                  found a direction
 */
class EyeAnalyser
{
public:
    /*!
     * \brief EyeAnalyser           constructor, set initial sensibility value
     *                              and clear varibles
     */
    EyeAnalyser();

    /*!
     * \brief getDirection          compare the direction of both eyes and return the direction if
     *                              both eyes direction are the same
     * \param calibrationLeft       Calibration value of left Eye
     * \param calibrationRight      Calibration value of right Eye
     * \param leftEye               deque<Point> of recent detected left Eyes
     * \param rightEye              deque<Point> of recent detected right Eyes
     * \return                      1-center  2-right  3-up 4-left 5-down
     */
    short getDirection(const Point &calibrationLeft,const Point &calibrationRight,const deque<Point> &leftEye,const deque<Point> &rightEye);

    /*!
     * \brief getDistance           Compute the distance and angle between the calibration
     *                              and median of deque Eye.  Based on that distance and angle
     *                              the direction is returned
     * \param calibration           Calibration value of one Eye
     * \param Eye                   deque<Point> of recent detected left Eyes
     * \return                      1-center  2-right  3-up 4-left 5-down
     */
    short getDistance(const Point &calibration,const deque<Point> &Eye);

    /*!
     * \brief setSensibility        set value of variable Sensibility
     * \param newValue              new value of sensibility
     */
    void setSensibility(const int &newValue);

private:
    /*!
     * \brief medianPoint   Compute the median of deque<Point>
     * \param input         deque<Point> in which the median is extracted
     * \return              return a Point with mediaPoint in X and Y
     */
    Point medianPoint(const deque<Point> &input);

    /*!
     * \brief sensibility   value used as baseline to compute the direction
     *                      High value of sensibility means that it is necessary
     *                      big difference between calibration and actual position
     */
    int m_sensibility;

    /*!
     * \brief m_centers     vector that contain points
     */
    std::vector<cv::Point> m_centers;

};

#endif // EYEANALYSER_H
