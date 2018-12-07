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
#include "USBCamera.h"
#include "icamera.h"
#include "dataBufferPool.h"

using namespace std;

/*!
 * \brief The BaseCameraFactory class
 */
class BaseCameraFactory{

public:
    /*!
     * \brief BaseCameraFactory
     */
    BaseCameraFactory(){}
    ~BaseCameraFactory(){}

    /*!
     * \brief CreateCamera
     * \param control
     * \param dataPool
     * \param CameraType
     * \return
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
