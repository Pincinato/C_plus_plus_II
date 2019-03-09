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
 * \brief The EyeDetector               Aims to detected the face and eyes in a certain frame and
 *                                      draw circles of retangles around the detected object.
 */
class EyeDetector
{
public:
    /*!
     * \brief EyeDetector       initialize variables and cascades
     */
    EyeDetector();
    ~EyeDetector();

    /*!
     * \brief detectEyes
     * \param frame             const Mat & that contain the frame to be analysed
     * \param faces             vector<Rect> where the detected faces will be saved
     * \param eyes              vector<Rect> where the detected eyes will be saved
     * \return                  true if faces and eyes were detected; otherwise false
     */
    bool detectEyes(const Mat &frame, vector<Rect> &faces,vector<Rect> &eyes);

    /*!
     * \brief getRightEye       detected the eyes localized in the most right of the face
     * \param eyes              vector<Rect> that contains the eyes
     * \return                  true if an eye were detected; otherwise false
     */
    Rect getRightEye(const vector<Rect> &eyes);

    /*!
     * \brief getLeftEye        detected the eyes localized in the most left of the face
     * \param eyes              vector<Rect> that contains the eyes
     * \return                  true if an eye were detected; otherwise false.
     */
    Rect getLeftEye(const vector<Rect> &eyes);

    /*!
     * \brief drawEyes          draw circles around the eyes regions in a frame
     * \param frame             Mat & in which a circles will be drawn
     * \param faces             vector<Rect> with face
     * \param eyes              vector<Rect> with eyes
     * \return                  true if circles were drawn; otherwise false.
     */
    bool drawEyes( Mat &frame,const vector<Rect> &faces,const vector<Rect> &eyes);

    /*!
     * \brief drawFaces         draw retangle around the eyes regions in a frame
     * \param frame             Mat & in which a retangle will be drawn
     * \param faces             vector<Rect> with faces
     * \return                  true if a retangle was drawn; otherwise false.
     */
    bool drawFaces(Mat &frame,const vector<Rect> &faces);

    /*!
     * \brief detectCenterLeftEye       detect the center of the left Eye
     * \param faces                     vector<Rect> with faces
     * \param eyes                      vector<Rect> with eyes
     * \return                          a Point to the center of the left Eye
     */
    Point detectCenterLeftEye(const vector<Rect> &faces,const  vector<Rect> &eyes);

    /*!
     * \brief detectCenterRightEye      detect the center of the right Eye
     * \param faces                     vector<Rect> with faces
     * \param eyes                      vector<Rect> with eyes
     * \return                          a Point to the center of the right Eye
     */
    Point detectCenterRightEye(const vector<Rect> &faces,const  vector<Rect> &eyes);

    /*!
     * \brief drawBothCenterEye         draw a small circle around the eyes centers in a frame
     * \param faces                     Mat & in which the circle will be drawn
     * \param eyes                      vector<Rect> with eyes
     * \return                          true if the centers were detected; otherwise false.
     */
    bool drawBothCenterEye(const vector<Rect> &faces,const vector<Rect> &eyes);

    /*!
     * \brief drawEyesCenter            draw a small circle around an eye center
     * \param frame                     Mat & in which the circle will be drawn
     * \param eye_center                Point to the eye center
     * \return                          true if small circles are drawn; otherwise false.
     */
    bool drawEyesCenter(Mat &frame,const Point & eye_center);

    /*!
     * \brief cascadeIsLoaded           get to the cascade variable
     * \return                          cascade variable
     */
    bool cascadeIsLoaded();

private:
    /*!
     * \brief m_face_cascade_name       string  that contains the path to the face cascade file (.xml)
     */
    std::string m_face_cascade_name;

    /*!
     * \brief m_eyes_cascade_name       string  that contains the path to the eye cascade file (.xml)
     */
    std::string m_eyes_cascade_name;

    /*!
     * \brief m_face_cascade           Cascade variable of open cv, used for the face detection
     */
    cv::CascadeClassifier m_face_cascade;

    /*!
     * \brief m_eyes_cascade            Cascade variable of open cv, used for the eyes detection
     */
    cv::CascadeClassifier m_eyes_cascade;

    /*!
     * \brief cascade                   bool value used to storage the state of cascade
     *
     */
    bool cascade;
};

#endif // eyeDetector_H
