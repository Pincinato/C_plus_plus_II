#ifndef IWIDGET_H
#define IWIDGET_H

#include "dataBuffer.h"

class IWidget
{
public:
    IWidget(){}
    virtual ~IWidget(){ }
    virtual void displayMsg(std::string tag, std::string msg)=0;
    virtual void setData(DataBufferPtr data)=0;

};

#endif // IWIDGET_H
