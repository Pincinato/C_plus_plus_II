#ifndef BASECAMERAFACTORY_H
#define BASECAMERAFACTORY_H

#include <memory>
#include <iostream>
#include <string>

#include "VCamera.h"
#include "vrgbcamera.h"
#include "icamera.h"
#include "dataBufferPool.h"

using namespace std;


class BaseCameraFactory{

public:
    BaseCameraFactory(){}
    ~BaseCameraFactory(){}
    unique_ptr<BaseCamera> CreateCamera(ICamera *control, std::shared_ptr<DataBufferPool> dataPool,const string &CameraType){

        if(CameraType=="VCamera"){
           return unique_ptr<BaseCamera>(new VCamera(control,dataPool));
        }
        else if (CameraType=="RGBCamera") {
            return unique_ptr<BaseCamera>(new VrgbCamera (control,dataPool));
        }
        return nullptr;
    }

};

#endif // BASECAMERAFACTORY_H
