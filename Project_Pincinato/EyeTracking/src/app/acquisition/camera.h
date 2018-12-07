/****************************************************************************
** Copyright (c) 2018 University of Bern & Bern University of Applied Science
** Project: Eye tracking
**
** Contact:  Thiago Henrique Pincianto ( thiago.pincinato@bfh.ch )
*****************************************************************************/
#ifndef BASECAMERA_H
#ifndef CAMERA_H
#define CAMERA_H


#include "dataBuffer.h"
#include "basecamera.h"
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;
// Forward declarations
class ICamera;
class DataBufferPool;

/*!
 * \brief The Camera class
 */
class Camera : public BaseCamera
{
public:
    /*!
     * \brief Camera
     * \param control
     * \param dataPool
     */
    Camera(ICamera* control, std::shared_ptr<DataBufferPool> dataPool);
    virtual  ~Camera();

    /*!
     * \brief startPlayData
     */
    virtual void startPlayData()=0;

    /*!
     * \brief stop
     */
    virtual void stop()=0;

    /*!
     * \brief isPlaying
     * \return
     */
    bool isPlaying();

    /*!
     * \brief setPlayRate
     * \param playRate
     */
    void setPlayRate(const int &playRate);


protected:
    /*!
     * \brief readImage
     * \param data
     * \return
     */
    bool readImage(DataBufferPtr data);

    /*!
     * \brief bgrToGray
     * \param src
     * \param dst
     */
    void bgrToGray(const Mat &src, Mat & dst);

    /*!
     * \brief bgrToRgb
     * \param dst
     */
    void bgrToRgb( Mat & dst);

    /*!
     * \brief m_tag
     */
    std::string m_tag;

    /*!
     * \brief m_play
     */
    bool m_play;

    /*!
     * \brief m_capture
     */
    VideoCapture m_capture;

    /*!
     * \brief m_control
     */
    ICamera* m_control;

    /*!
     * \brief m_playRate
     */
    int m_playRate;

    /*!
     * \brief m_dataPool
     */
    std::shared_ptr<DataBufferPool> m_dataPool;

    /*!
     * \brief m_offset
     */
    size_t m_offset;

};

#endif // CAMERA_H
