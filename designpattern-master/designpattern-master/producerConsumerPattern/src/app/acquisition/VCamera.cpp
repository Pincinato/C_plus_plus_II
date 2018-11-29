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

VCamera::~VCamera()
{
    // Thread stopping
    m_play = false;

    if(m_acquireThread.joinable())
    {
        m_acquireThread.join();
    }
    if(capture.isOpened()){
        capture.release();
    }
}

void VCamera::startPlayData()
{
    m_play = true;
    capture.open(0);
    m_acquireThread = std::thread(&VCamera::run, this);
    m_control->displayMsg(m_tag, "Start Playing");
}

void VCamera::stop()
{
    m_play = false;
    m_control->displayMsg(m_tag, "Stop playing");
    if(capture.isOpened()){
        capture.release();
    }
}

bool VCamera::isPlaying()
{
    return m_play;
}

void VCamera::setPlayRate(int playRate)
{
    m_playRate = playRate;
}

//******* Below runs in own thread **********//
void VCamera::run()
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

bool VCamera::readImage(DataBufferPtr data)
{
    bool ACK=false;
    //capture.read(data->m_frame);
    capture >> data->m_frame;
    //Mat frame_gray(256,256,CV_8UC1);
    //cvtColor(data->m_frame, frame_gray, COLOR_BGR2GRAY );
    if(!data->m_frame.empty()){
        data->m_image =QImage(data->m_frame.data,data->m_frame.cols,data->m_frame.rows,data->m_frame.step,QImage::Format_RGB888);
        ACK=true;
    }
    return ACK;
}