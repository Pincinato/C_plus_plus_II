#ifndef ICAMERA_H
#define ICAMERA_H

#include "dataBuffer.h"

class ICamera
{
public:
    ICamera(){}
    virtual ~ICamera(){}
    virtual void displayMsg(const std::string &tag, const std::string &msg)=0;
    virtual void setData(DataBufferPtr dataJunk)=0;

};

#endif // ICAMERA_H
