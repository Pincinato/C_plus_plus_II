#include "camera.h"

Camera::Camera(ICamera *control, std::shared_ptr<DataBufferPool> dataPool) :
    BaseCamera(control,dataPool),
    m_tag("Base player"),
    m_play(false),
    m_control(control),
    m_playRate(33),
    m_dataPool(dataPool),
    m_offset(0)
{

}

Camera::~Camera()
{

}

bool Camera::isPlaying()
{
    return m_play;
}

void Camera::setPlayRate(int playRate)
{
    m_playRate = playRate;
}


bool Camera::readImage(DataBufferPtr data)
{
    bool ACK=false;
    m_capture >> data->m_frame;
    if(!data->m_frame.empty()){
        bgrToGray(data->m_frame, data->m_frameGray);
        data->m_image =QImage(data->m_frame.data,data->m_frame.cols,data->m_frame.rows,static_cast<int>(data->m_frame.step),QImage::Format_RGB888);
        ACK=true;
    }
    return ACK;
}

void Camera::bgrToGray(const cv::Mat& src, cv::Mat& dst)
{

    CV_Assert(src.type() == CV_8UC3);
    int rows = src.rows, cols = src.cols;
    /*
    vector<uchar> vec(static_cast<uint>(rows*cols));
    if(src.isContinuous()){
        vec.assign(src.datastart,src.dataend);
    }
    else{}
*/
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
            dst_ptr[col] = static_cast<uchar>((src_ptr[2] * 0.114f + src_ptr[1] * 0.587f + src_ptr[0] * 0.299f));
            src_ptr += 3;
        }
    }
}

