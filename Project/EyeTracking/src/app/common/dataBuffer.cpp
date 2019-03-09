/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#include "dataBuffer.h"

DataBuffer::DataBuffer(const uint& height, const uint& width )
{
    m_image = QImage(static_cast<const int>(height), static_cast<const int>(width), QImage::Format_RGB888);
    m_frame = cv::Mat(static_cast<const int>(height),static_cast<const int>(width),CV_8UC3);
    m_frameGray= cv::Mat(static_cast<const int>(height),static_cast<const int>(width),CV_8UC1);
}


