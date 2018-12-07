/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#ifndef VIDEOVISUALIZER_H
#define VIDEOVISUALIZER_H

#include <memory>
#include <QWidget>
#include <QImage>
#include "dataBuffer.h"

class QLabel;
class QVBoxLayout;
class rOg_image;

class VideoVisualizer : public QWidget
{
public:
    /*!
     * \brief VideoVisualizer
     * \param parent
     */
    VideoVisualizer( QWidget *parent = 0 );
    ~VideoVisualizer();

    /*!
     * \brief setScan
     * \param dataData
     */
    void setScan(DataBufferPtr dataData);

private:
    /*!
     * \brief redrawFrame
     */
    void redrawFrame();
    std::unique_ptr<rOg_image> m_imgWidget;
    std::unique_ptr<QVBoxLayout> m_layout;
    QImage m_image;
    bool m_firstFrame;
};

#endif  // VIDEOVISUALIZER_H
