#ifndef USBCAMERA_H
#define USBCAMERA_H

#include <thread>
#include "dataBuffer.h"
#include "camera.h"
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;
// Forward declarations
class ICamera;
class DataBufferPool;

class USBCamera final: public Camera
{
public:
    USBCamera(ICamera* control, std::shared_ptr<DataBufferPool> dataPool);
    ~USBCamera()override;

    void startPlayData() override;
    void stop() override;

private:
     void run() ;
     std::thread m_acquireThread;

};

#endif // USBCAMERA_H
