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
      * \brief VCamera
      * \param control
      * \param dataPool
      */
     VCamera(ICamera* control, std::shared_ptr<DataBufferPool> dataPool);
     ~VCamera()override;

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
     void run();

     /*!
      * \brief m_acquireThread
      */
     std::thread m_acquireThread;

};

#endif // VCAMERA_H
