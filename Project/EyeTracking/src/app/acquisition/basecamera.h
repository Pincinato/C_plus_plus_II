/****************************************************************************
** Copyright (c) 2018 University of Bern & Bern University of Applied Science
** Project: Eye tracking
**
** Contact:  Thiago Henrique Pincianto ( thiago.pincinato@bfh.ch )
*****************************************************************************/
#ifndef BASECAMERA_H
#define BASECAMERA_H


#include "icamera.h"
#include "dataBufferPool.h"

/*!
 * \brief The BaseCamera class      This class is an interface class for the object camera.
 *                                  This class is also used for the factory pattern
 *
 */
class BaseCamera{

public:
    /*!
     * \brief BaseCamera        Contructor of Base class with initialize list
     * \param control           Pointer to an ICamera object
     * \param dataPool          Shared pointer to a DataBufferPool
     */
    BaseCamera(ICamera *control, std::shared_ptr<DataBufferPool> dataPool):
        m_control(control),m_dataPool(dataPool){}
    virtual ~BaseCamera(){}

    /*!
     * \brief startPlayData     pure virtual method
     */
    virtual void startPlayData()=0;

    /*!
     * \brief stop              pure virtual method
     */
    virtual void stop()=0;

    /*!
     * \brief isPlaying         pure virtual method
     * \return
     */
    virtual bool isPlaying()=0;

    /*!
     * \brief setPlayRate       pure virtual method
     * \param playRate          const int &
     */
    virtual void setPlayRate(const int &playRate)=0;

protected:
    /*!
     * \brief m_control         pointer to a ICamera object
     */
    ICamera* m_control;

    /*!
     * \brief m_dataPool        shared pointer to DataBufferPool
     */
    std::shared_ptr<DataBufferPool> m_dataPool;

};

#endif // BASECAMERA_H
