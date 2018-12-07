/****************************************************************************
** Copyright (c) 2018 University of Bern & Bern University of Applied Science
** Project: Eye tracking
**
** Contact:  Thiago Henrique Pincianto ( thiago.pincinato@bfh.ch )
*****************************************************************************/
#ifndef BASECAMERA_H
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

/*!
 * \brief The USBCamera class
 */
class USBCamera final: public Camera
{
public:
    /*!
     * \brief USBCamera
     * \param control
     * \param dataPool
     */
    USBCamera(ICamera* control, std::shared_ptr<DataBufferPool> dataPool);      
    ~USBCamera()override;


    /*!
     * \brief startPlayData
     */
    void startPlayData() override;


    /*!
     * \brief stop
     */
    void stop() override;

private:
    /*!
      * \brief run
      */
     void run() ;

     /*!
      * \brief m_acquireThread
      */
     std::thread m_acquireThread;

};

#endif // USBCAMERA_H
