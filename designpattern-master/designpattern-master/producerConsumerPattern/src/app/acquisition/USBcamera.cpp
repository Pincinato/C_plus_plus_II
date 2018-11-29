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
    BaseCamera(control,dataPool),
    m_tag("Player"),
    m_play(false),
    m_control(control),
    m_playRate(33),
    m_dataPool(dataPool),
    offset(0)
{
    m_control->displayMsg(m_tag, "Player constructed");
}

USBCamera::~USBCamera()
{
    // Thread stopping
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
    capture.open(1);
    m_acquireThread = std::thread(&USBCamera::run, this);
    m_control->displayMsg(m_tag, "Start Playing");;
}

void USBCamera::stop()
{
    m_play = false;
    m_control->displayMsg(m_tag, "Stop playing");
    if(capture.isOpened()){
        capture.release();
    }
}

bool USBCamera::isPlaying()
{
    return m_play;
}

void USBCamera::setPlayRate(int playRate)
{
    m_playRate = playRate;
}

//******* Below runs in own thread **********//
void USBCamera::run()
{
    while( (m_play) & (capture.isOpened()))
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

bool USBCamera::readImage(DataBufferPtr data)
{
    bool ACK=false;
    capture >> data->m_frame;
    if(!data->m_frame.empty()){
        data->m_image =QImage(data->m_frame.data,data->m_frame.cols,data->m_frame.rows,data->m_frame.step,QImage::Format_RGB888);
        ACK=true;
    }
    return ACK;
}
