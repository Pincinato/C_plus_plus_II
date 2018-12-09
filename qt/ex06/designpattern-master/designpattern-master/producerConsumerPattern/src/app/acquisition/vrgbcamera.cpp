/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#include <chrono>
#include "dataBufferPool.h"
#include "icamera.h"
#include "vrgbcamera.h"

VrgbCamera::VrgbCamera(ICamera *control, std::shared_ptr<DataBufferPool> dataPool) :
    BaseCamera(control,dataPool),
    m_tag("Player"),
    m_play(false),
    m_playRate(33),
    offset(0)

{
    m_control->displayMsg(m_tag, "Player RGBcamera constructed");
}

VrgbCamera::~VrgbCamera()
{
    // Thread stopping
    m_play = false;

    if(m_acquireThread.joinable())
    {
        m_acquireThread.join();
    }
    m_control->displayMsg(m_tag, "Player RGBCamera destroyed");
}

void VrgbCamera::startPlayData()
{
    m_play = true;
    m_acquireThread = std::thread(&VrgbCamera::run, this);
    m_control->displayMsg(m_tag, "Start Playing");
}

void VrgbCamera::stop()
{
    m_play = false;
    m_control->displayMsg(m_tag, "Stop playing");
}

bool VrgbCamera::isPlaying()
{
    return m_play;
}

void VrgbCamera::setPlayRate(int playRate)
{
    m_playRate = playRate;
}

//******* Below runs in own thread **********//
void VrgbCamera::run()
{
    while( m_play )
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

bool VrgbCamera::readImage(DataBufferPtr data)
{
    int width = data->m_image.width();
    int height = data->m_image.height();

    for(int y = 0; y < height; y++)
    {

        for(int x = 0; x < width; x++)
        {
            int val = x + offset;
            if(y<height/3){
                data->m_image.setPixel(x, y, qRgb(val, 0 ,0));
            }
            else if(y<2*height/3){
                data->m_image.setPixel(x, y, qRgb(0, val ,0));
            }
            else{
                data->m_image.setPixel(x, y, qRgb(0, 0 ,val));
            }
        }
    }
    offset+= 25;
    return true;
}
