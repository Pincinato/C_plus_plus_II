#ifndef CAMERA_H
#define CAMERA_H


#include "dataBuffer.h"
#include "basecamera.h"
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;
// Forward declarations
class ICamera;
class DataBufferPool;

class Camera : public BaseCamera
{
public:
    Camera(ICamera* control, std::shared_ptr<DataBufferPool> dataPool);
    virtual  ~Camera();
    virtual void startPlayData()=0;
    virtual void stop()=0;
    bool isPlaying();
    void setPlayRate(int playRate);

protected:

    bool readImage(DataBufferPtr data);
    void bgrToGray(const Mat &src, Mat & dst);
    std::string m_tag;
    bool m_play;
    VideoCapture m_capture;
    ICamera* m_control;
    int m_playRate;
    std::shared_ptr<DataBufferPool> m_dataPool;
    size_t m_offset;

};

#endif // CAMERA_H
