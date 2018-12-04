/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#include <chrono>
#include "VCamera.h"
#include "dataBufferPool.h"
#include "icamera.h"

VCamera::VCamera(ICamera *control, std::shared_ptr<DataBufferPool> dataPool) :
    Camera(control,dataPool)
{
    m_tag ="VCamera";
    m_control->displayMsg(m_tag, "Player constructed");
}

VCamera::~VCamera()
{
    // Thread stopping
    m_play = false;

    if(m_acquireThread.joinable())
    {
        m_acquireThread.join();
    }
    if(m_capture.isOpened()){
        m_capture.release();
    }
}

void VCamera::startPlayData()
{
    m_play = true;
    m_capture.open(0);
    m_acquireThread = std::thread(&VCamera::run, this);
    m_control->displayMsg(m_tag, "Start Playing");
}

void VCamera::stop()
{
    m_play = false;
    m_control->displayMsg(m_tag, "Stop playing");
    if(m_capture.isOpened()){
        m_capture.release();
    }
}

//******* Below runs in own thread **********//
void VCamera::run()
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

