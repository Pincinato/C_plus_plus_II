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
    m_offset(0)
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

bool VCamera::readImage(DataBufferPtr data)
{
    bool ACK=false;
    //capture.read(data->m_frame);
    m_capture >> data->m_frame;
    //Mat frame_gray(256,256,CV_8UC1);

    if(!data->m_frame.empty()){
        bgrToGray(data->m_frame, data->m_frameGray);
        data->m_image =QImage(data->m_frame.data,data->m_frame.cols,data->m_frame.rows,data->m_frame.step,QImage::Format_RGB888);
        ACK=true;
    }
    return ACK;
}

void VCamera::bgrToGray(const cv::Mat& src, cv::Mat& dst)
{
    CV_Assert(src.type() == CV_8UC3);
    int rows = src.rows, cols = src.cols;

    dst.create(src.size(), CV_8UC1);

    if (src.isContinuous() && dst.isContinuous())
    {
        cols = rows * cols;
        rows = 1;
    }

    for (int row = 0; row < rows; ++row)
    {
        const uchar* src_ptr = src.ptr<uchar>(row);
        uchar* dst_ptr = dst.ptr<uchar>(row);

        for (int col = 0; col < cols; ++col)
        {
            dst_ptr[col] = (uchar)(src_ptr[2] * 0.114f + src_ptr[1] * 0.587f + src_ptr[0] * 0.299f);
            src_ptr += 3;
        }
    }
}
