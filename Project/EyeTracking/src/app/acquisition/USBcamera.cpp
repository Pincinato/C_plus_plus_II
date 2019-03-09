/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#include <chrono>
#include "dataBufferPool.h"
#include "icamera.h"
#include "USBcamera.h"

USBCamera::USBCamera(ICamera *control, std::shared_ptr<DataBufferPool> dataPool) :
    Camera(control,dataPool)
{
    m_tag="USBCamera";
    m_control->displayMsg(m_tag, "Player constructed");
}

USBCamera::~USBCamera()
{
    m_play = false;
    if(m_acquireThread.joinable())
    {
        m_acquireThread.join();
    }
    m_control->displayMsg(m_tag, "Player RGBCamera destroyed");
}

void USBCamera::startPlayData()
{
    m_play = true;
    m_capture.open(1);
    m_acquireThread = std::thread(&USBCamera::run, this);
    m_control->displayMsg(m_tag, "Start Playing");;
}

void USBCamera::stop()
{
    m_play = false;
    m_control->displayMsg(m_tag, "Stop playing");
    if(m_capture.isOpened()){
        m_capture.release();
    }
}

//******* Below runs in own thread **********//
void USBCamera::run()
{
    while( (m_play) & (m_capture.isOpened()))
    {
        DataBufferPtr nextPtr = m_dataPool->getBuffer();
        if( readImage(nextPtr) )
        {
            m_control->setData(nextPtr);
        }
        // Control frame rate
        int sleeptime = static_cast<int>( 1000.0f/m_playRate ) ;
        std::this_thread::sleep_for( std::chrono::milliseconds( sleeptime ));
    }
}
