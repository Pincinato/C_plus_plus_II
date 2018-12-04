#ifndef USBCAMERA_H
#define USBCAMERA_H

#include <thread>
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

class USBCamera final: public BaseCamera
{
public:
    USBCamera(ICamera* control, std::shared_ptr<DataBufferPool> dataPool);
    ~USBCamera()override;

    void startPlayData() override;
    void stop() override;
    bool isPlaying() override;
    void setPlayRate(int playRate) override;

private:
     void run() ;
     bool readImage(DataBufferPtr data);
     void bgrToGray(const Mat &src, Mat & dst);
     std::string m_tag;
     std::thread m_acquireThread;
     bool m_play;
     VideoCapture m_capture;
     ICamera* m_control;
     int m_playRate;
     std::shared_ptr<DataBufferPool> m_dataPool;
     size_t m_offset;
};

#endif // USBCAMERA_H
