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
 * \brief The BaseCamera class
 */
class BaseCamera{

public:
    /*!
     * \brief BaseCamera
     * \param control
     * \param dataPool
     */
    BaseCamera(ICamera *control, std::shared_ptr<DataBufferPool> dataPool):
        m_control(control),m_dataPool(dataPool){}
    virtual ~BaseCamera(){}

    /*!
     * \brief startPlayData
     */
    virtual void startPlayData()=0;

    /*!
     * \brief stop
     */
    virtual void stop()=0;

    /*!
     * \brief isPlaying
     * \return
     */
    virtual bool isPlaying()=0;

    /*!
     * \brief setPlayRate
     * \param playRate
     */
    virtual void setPlayRate(const int &playRate)=0;

protected:
    /*!
     * \brief m_control
     */
    ICamera* m_control;

    /*!
     * \brief m_dataPool
     */
    std::shared_ptr<DataBufferPool> m_dataPool;

};

#endif // BASECAMERA_H
