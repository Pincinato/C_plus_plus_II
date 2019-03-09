#include "camera.h"

Camera::Camera(ICamera *control, std::shared_ptr<DataBufferPool> dataPool) :
    BaseCamera(control,dataPool),
    m_tag("Base player"),
    m_play(false),
    m_playRate(33)
{

}

Camera::~Camera()
{

}

bool Camera::isPlaying()
{
    return m_play;
}

void Camera::setPlayRate(const int &playRate)
{
    m_playRate = playRate;
}


bool Camera::readImage(DataBufferPtr data)
{
    bool ACK=false;
    m_capture >> data->m_frame;
    if(!data->m_frame.empty()){
        bgrToGray(data->m_frame, data->m_frameGray);
        bgrToRgb(data->m_frame);
        data->m_image =QImage(data->m_frame.data,data->m_frame.cols,data->m_frame.rows,static_cast<int>(data->m_frame.step),QImage::Format_RGB888);
        ACK=true;
    }
    return ACK;
}

void Camera::bgrToGray(const cv::Mat& src, cv::Mat& dst)
{

    CV_Assert(src.type() == CV_8UC3);
    dst.create(src.size(), CV_8UC1);
    for (int row = 0; row <  src.rows; ++row)
    {
        for (int col = 0; col < src.cols; ++col)
        {
            dst.at<uchar>(row,col) =static_cast<uchar>(src.at<uchar>(row,(3*col)+2) * 0.114f + src.at<uchar>(row,(3*col)+1) * 0.587f + src.at<uchar>(row,(3*col)) * 0.299f);
        }
    }

}


void Camera::bgrToRgb(cv::Mat& image)
{

    CV_Assert(image.type() == CV_8UC3);
    uchar aux1;
    for (int row = 0; row <  image.rows; ++row)
    {
        for (int col = 0; col < 3*image.cols; col+=3)
        {
            aux1= image.at<uchar>(row,col+2);
            image.at<uchar>(row,col+2) = image.at<uchar>(row,col+0);
            image.at<uchar>(row,col+0)= aux1;
        }
    }
}

