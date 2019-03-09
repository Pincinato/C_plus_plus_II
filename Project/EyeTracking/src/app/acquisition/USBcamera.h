/****************************************************************************
** Copyright (c) 2018 University of Bern & Bern University of Applied Science
** Project: Eye tracking
**
** Contact:  Thiago Henrique Pincianto ( thiago.pincinato@bfh.ch )
*****************************************************************************/

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
 *
 * Note: Inheritating is not allowed since starting a thread in the constructor can be problematic for derived classes
 */
class USBCamera final: public Camera
{
public:
    /*!
     * \brief USBCamera         Constructor
     * \param control           Icamera pointer
     * \param dataPool          DataBufferPool
     */
    USBCamera(ICamera* control, std::shared_ptr<DataBufferPool> dataPool);      
    ~USBCamera()override;


    /*!
     * \brief startPlayData     open Video Capture, and start thread
     */
    void startPlayData() override;


    /*!
     * \brief stop              close video Capture, and stop thread
     */
    void stop() override;

private:
    /*!
      * \brief run              Capture image and set data.
      */
     void run() ;

     /*!
      * \brief m_acquireThread   Thread resposible to acquire frame.
      */
     std::thread m_acquireThread;

};

#endif // USBCAMERA_H
