/****************************************************************************
** Copyright (c) 2018 University of Bern & Bern University of Applied Science
** Project: Eye tracking
**
** Contact:  Thiago Henrique Pincianto ( thiago.pincinato@bfh.ch )
*****************************************************************************/
#ifndef ICONTROL_H
#define ICONTROL_H


#include "dataBuffer.h"

/*!
 * \brief The IControl class        interface class of control
 */
class IControl {
public:
    /*!
     * \brief IControl      constructor method
     */
    IControl(){}
    virtual ~IControl(){}
    /*!
     * \brief displayMsg    virtual method
     */
    virtual void displayMsg(const std::string &tag, const std::string &msg) =0;

    /*!
     * \brief setData       virtual method
     */
    virtual void setData(DataBufferPtr dataJunk) =0;

    /*!
     * \brief setPoint      virtual method
     */
    virtual void setPoint(const cv::Point &eyeLeft,const cv::Point &eyeRight)=0;

};

#endif // ICONTROL_H
