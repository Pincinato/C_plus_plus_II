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
 * \brief The EyeAnalyser class
 */
class EyeAnalyser
{
public:
    /*!
     * \brief EyeAnalyser
     */
    EyeAnalyser();

    /*!
     * \brief getDirection
     * \param calibrationLeft
     * \param calibrationRight
     * \param leftEye
     * \param rightEye
     * \return
     */
    short getDirection(const Point &calibrationLeft,const Point &calibrationRight,const deque<Point> &leftEye,const deque<Point> &rightEye);

    /*!
     * \brief getDistance
     * \param calibration
     * \param Eye
     * \return
     */
    short getDistance(const Point &calibration,const deque<Point> &Eye);

    /*!
     * \brief setSensibility
     * \param newValue
     */
    void setSensibility(const int &newValue);

private:
    /*!
     * \brief medianPoint
     * \param input
     * \return
     */
    Point medianPoint(const deque<Point> &input);

    /*!
     * \brief sensibility
     */
    int sensibility;

    /*!
     * \brief m_valueX
     */
    deque<int> m_valueX;

    /*!
     * \brief m_valueY
     */
    deque<int> m_valueY;

    /*!
     * \brief m_centers
     */
    std::vector<cv::Point> m_centers;

};

#endif // EYEANALYSER_H
