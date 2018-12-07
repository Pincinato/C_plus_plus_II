/****************************************************************************
** Copyright (c) 2018 University of Bern & Bern University of Applied Science
** Project: Eye tracking
**
** Contact:  Thiago Henrique Pincianto ( thiago.pincinato@bfh.ch )
*****************************************************************************/
#ifndef eyeDetector_H
#define eyeDetector_H


#include <QWidget>
#include <memory>
#include "icamera.h"
#include <QTimer>
#include <QImage>


#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;

// Forward declarations
class VCamera;
class DataBufferPool;

/*!
 * \brief The EyeDetector class
 */
class EyeDetector
{
public:
    /*!
     * \brief EyeDetector
     */
    EyeDetector();
    ~EyeDetector();

    /*!
     * \brief detectEyes
     * \param frame
     * \param faces
     * \param eyes
     * \return
     */
    bool detectEyes(const Mat &frame, vector<Rect> &faces,vector<Rect> &eyes);

    /*!
     * \brief getRightEye
     * \param eyes
     * \return
     */
    Rect getRightEye(const vector<Rect> &eyes);

    /*!
     * \brief getLeftEye
     * \param eyes
     * \return
     */
    Rect getLeftEye(const vector<Rect> &eyes);

    /*!
     * \brief drawEyes
     * \param frame
     * \param faces
     * \param eyes
     * \return
     */
    bool drawEyes( Mat &frame,const vector<Rect> &faces,const vector<Rect> &eyes);

    /*!
     * \brief drawFaces
     * \param frame
     * \param faces
     * \return
     */
    bool drawFaces(Mat &frame,const vector<Rect> &faces);

    /*!
     * \brief detectCenterLeftEye
     * \param faces
     * \param eyes
     * \return
     */
    Point detectCenterLeftEye(const vector<Rect> &faces,const  vector<Rect> &eyes);

    /*!
     * \brief detectCenterRightEye
     * \param faces
     * \param eyes
     * \return
     */
    Point detectCenterRightEye(const vector<Rect> &faces,const  vector<Rect> &eyes);

    /*!
     * \brief drawBothCenterEye
     * \param faces
     * \param eyes
     * \return
     */
    bool drawBothCenterEye(const vector<Rect> &faces,const vector<Rect> &eyes);

    /*!
     * \brief drawEyesCenter
     * \param frame
     * \param eye_center
     * \return
     */
    bool drawEyesCenter(Mat &frame,const Point & eye_center);

    /*!
     * \brief cascadeIsLoaded
     * \return
     */
    bool cascadeIsLoaded();

private:
    /*!
     * \brief m_face_cascade_name
     */
    std::string m_face_cascade_name;

    /*!
     * \brief m_eyes_cascade_name
     */
    std::string m_eyes_cascade_name;

    /*!
     * \brief m_face_cascade
     */
    cv::CascadeClassifier m_face_cascade;

    /*!
     * \brief m_eyes_cascade
     */
    cv::CascadeClassifier m_eyes_cascade;

    /*!
     * \brief cascade
     */
    bool cascade;
};

#endif // eyeDetector_H
