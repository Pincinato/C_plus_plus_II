/****************************************************************************
** Copyright (c) 2018 University of Bern & Bern University of Applied Science
** Project: Eye tracking
**
** Contact:  Thiago Henrique Pincianto ( thiago.pincinato@bfh.ch )
*****************************************************************************/

#ifndef VCAMERA_H
#define VCAMERA_H

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

/**
 * @brief The VCamera class
 *
 * Note: Inheritating is not allowed since starting a thread in the constructor can be problematic for derived classes
 */
class VCamera final: public Camera
{

public:
    /*!
      * \brief VCamera          Constructor
     * \param control           Icamera pointer
     * \param dataPool          DataBufferPool
      */
     VCamera(ICamera* control, std::shared_ptr<DataBufferPool> dataPool);
     ~VCamera()override;

     /*!
      * \brief startPlayData    open Video Capture, and start thread
      */
     void startPlayData() override;


     /*!
      * \brief stop             close video Capture, and stop thread
      */
     void stop() override;



private:
     /*!
      * \brief run              Capture image and set data.
      */
     void run();

     /*!
      * \brief m_acquireThread  Thread resposible to acquire frame.
      */
     std::thread m_acquireThread;

};

#endif // VCAMERA_H
