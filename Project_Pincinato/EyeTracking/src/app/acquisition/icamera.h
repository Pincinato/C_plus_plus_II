/****************************************************************************
** Copyright (c) 2018 University of Bern & Bern University of Applied Science
** Project: Eye tracking
**
** Contact:  Thiago Henrique Pincianto ( thiago.pincinato@bfh.ch )
*****************************************************************************/
#ifndef ICAMERA_H
#define ICAMERA_H

#include "dataBuffer.h"

/*!
 * \brief The ICamera class
 */
class ICamera
{
public:
    /*!
     * \brief ICamera
     */
    ICamera(){}
    virtual ~ICamera(){}

    /*!
     * \brief displayMsg
     * \param tag
     * \param msg
     */
    virtual void displayMsg(const std::string &tag, const std::string &msg)=0;
    /*!
     * \brief setData
     * \param dataJunk
     */
    virtual void setData(DataBufferPtr dataJunk)=0;

};

#endif // ICAMERA_H
