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
 * \brief The ICamera class         interface class to camera
 */
class ICamera
{
public:
    /*!
     * \brief ICamera           dummy constructor
     */
    ICamera(){}
    virtual ~ICamera(){}

    /*!
     * \brief displayMsg        pure virtual method
     * \param tag               name of the instace
     * \param msg               msg of the instance
     */
    virtual void displayMsg(const std::string &tag, const std::string &msg)=0;
    /*!
     * \brief setData           pure virtual method
     * \param dataJunk          DataBufferPtr to the frame,image and gray frame.
     */
    virtual void setData(DataBufferPtr dataJunk)=0;

};

#endif // ICAMERA_H
