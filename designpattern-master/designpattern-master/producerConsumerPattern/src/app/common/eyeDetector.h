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

class EyeDetector
{
public:
    EyeDetector();
    ~EyeDetector();

    bool detectEyes(const Mat &frame, vector<Rect> &faces,vector<Rect> &eyes);
    Rect getRightEye(vector<Rect> &eyes);
    Rect getLeftEye(vector<Rect> &eyes);
    bool drawEyes( Mat &frame,vector<Rect> &faces, vector<Rect> &eyes);
    bool drawFaces(Mat &frame,vector<Rect> &faces);
    Point detectCenterLeftEye(std::vector<Rect> &faces, vector<Rect> &eyes);
    Point detectCenterRightEye(std::vector<Rect> &faces, vector<Rect> &eyes);
    bool drawBothCenterEye(std::vector<Rect> &faces, vector<Rect> &eyes);
    bool drawEyesCenter(Mat &frame, vector<Rect> &eyes,Point & eye_center);
private:


    std::string m_face_cascade_name;
    std::string m_eyes_cascade_name;
    cv::CascadeClassifier m_face_cascade;
    cv::CascadeClassifier m_eyes_cascade;

};

#endif // eyeDetector_H