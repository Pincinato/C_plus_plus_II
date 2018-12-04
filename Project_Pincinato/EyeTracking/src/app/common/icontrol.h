#ifndef ICONTROL_H
#define ICONTROL_H


#include "dataBuffer.h"


class IControl {
public:
    IControl(){}
    virtual ~IControl(){}
    virtual void displayMsg(const std::string &tag, const std::string &msg) =0;
    virtual void setData(DataBufferPtr dataJunk) =0;
    virtual void setPoint(const cv::Point &eyeLeft,const cv::Point &eyeRight) =0;

};

#endif // ICONTROL_H
