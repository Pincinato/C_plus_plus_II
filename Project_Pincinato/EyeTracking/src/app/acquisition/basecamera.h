#ifndef BASECAMERA_H
#define BASECAMERA_H


#include "icamera.h"
#include "dataBufferPool.h"

class BaseCamera{

public:
    BaseCamera(ICamera *control, std::shared_ptr<DataBufferPool> dataPool):
        m_control(control),m_dataPool(dataPool){}
    virtual ~BaseCamera(){}
    virtual void startPlayData()=0;
    virtual void stop()=0;
    virtual bool isPlaying()=0;
    virtual void setPlayRate(int playRate)=0;
protected:
    ICamera* m_control;
    std::shared_ptr<DataBufferPool> m_dataPool;

};

#endif // BASECAMERA_H
