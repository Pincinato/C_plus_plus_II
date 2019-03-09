/****************************************************************************
 *
** Copyright (c) 2018 University of Bern & Bern University of Applied Science
** Project: Eye tracking
**
** Contact:  Thiago Henrique Pincianto ( thiago.pincinato@bfh.ch )
*****************************************************************************/



#ifndef BASECAMERAFACTORY_H
#define BASECAMERAFACTORY_H

#include <memory>
#include <iostream>
#include <string>

#include "VCamera.h"
#include "USBcamera.h"
#include "icamera.h"
#include "dataBufferPool.h"

using namespace std;

/*!
 * \brief The BaseCameraFactory class       An factory class, factory pattern for
 *                                          the object VCamera and USBcamera.
 */
class BaseCameraFactory{

public:
    /*!
     * \brief BaseCameraFactory             Constructor, nothing is done.
     */
    BaseCameraFactory(){}
    ~BaseCameraFactory(){}

    /*!
     * \brief CreateCamera                  Function resposible to create new instance of Camera
     * \param control                       ICamera pointer that will be owned by the new Camera
     * \param dataPool                      DataBufferPool that will be owned by the new Camera
     * \param CameraType                    String used to select the camera, either WebCam or USBcamera
     * \return                              A nique pointer to the new created camera (BaseCamera)
     */
    unique_ptr<BaseCamera> CreateCamera(ICamera *control, std::shared_ptr<DataBufferPool> dataPool,const string &CameraType){

        if(CameraType=="WebCam"){
           return unique_ptr<BaseCamera>(new VCamera(control,dataPool));
        }
        else if (CameraType=="USBCamera") {
            return unique_ptr<BaseCamera>(new USBCamera (control,dataPool));
        }
        return nullptr;
    }

};

#endif // BASECAMERAFACTORY_H
