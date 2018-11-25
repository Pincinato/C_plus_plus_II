#ifndef EYE_DETECTOR_H
#define EYE_DETECTOR_H


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

class Eye_detector
{
public:
    Eye_detector();
    ~Eye_detector();

    bool detectEyes(const Mat &frame, vector<Rect> &faces,vector<Rect> &eyes);
    bool drawEyes( Mat &frame,vector<Rect> &faces, vector<Rect> &eyes);
    bool drawFaces(Mat &frame,vector<Rect> &faces);

private:


    std::string face_cascade_name;
    std::string eyes_cascade_name;
    cv::CascadeClassifier face_cascade;
    cv::CascadeClassifier eyes_cascade;

};

#endif // EYE_DETECTOR_H
