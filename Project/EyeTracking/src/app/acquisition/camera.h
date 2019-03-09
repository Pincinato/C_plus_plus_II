/****************************************************************************
** Copyright (c) 2018 University of Bern & Bern University of Applied Science
** Project: Eye tracking
**
** Contact:  Thiago Henrique Pincianto ( thiago.pincinato@bfh.ch )
*****************************************************************************/
#ifndef CAMERA_H
#define CAMERA_H


//#include "dataBuffer.h"
#include "basecamera.h"
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
using namespace std;
// Forward declarations
class ICamera;
class DataBufferPool;
class DataBuffer;

/*!
 * \brief The Camera class      Base class for Camera that implements the basic funtions
 *                              of the camera's obejcts (Vcamera and USBcamera).
 */
class Camera : public BaseCamera
{
public:
    /*!
     * \brief Camera            Constructor that initialize variable through initialization list
     * \param control           pointer to an Icamera
     * \param dataPool          shared ptr to DataBufferPool
     */
    Camera(ICamera* control, std::shared_ptr<DataBufferPool> dataPool);
    virtual  ~Camera();

    /*!
     * \brief startPlayData     vitual method
     */
    virtual void startPlayData()=0;

    /*!
     * \brief stop              vitual method
     */
    virtual void stop()=0;

    /*!
     * \brief isPlaying         function that return the m_play variable
     * \return                  true if camera is active, and false if not
     */
    bool isPlaying();

    /*!
     * \brief setPlayRate       sets the m_playRate
     * \param playRate          const int & that will be attributed to m_playRate
     */
    void setPlayRate(const int &playRate);


protected:
    /*!
     * \brief readImage         reads that actually read the camera and set the data frame
     * \param data              DataBufferPtr in which the actual frame, Qimage and a gray scale
     *                          frame will be storage
     * \return                  return true if a frame was captured and data variable were set.
     */
    bool readImage(DataBufferPtr data);

    /*!
     * \brief bgrToGray         Converts the frame(cv::Mat) in a BRG format to
     *                          a frame(cv::Mat) in GRAY format
     * \param src               const cv::Mat & source, 3 channels, BRG format
     * \param dst               cv::MAt & destination, 1 channel, GRAY format
     */
    void bgrToGray(const Mat &src, Mat & dst);

    /*!
     * \brief bgrToRgb          Converts the cv::Mat from BRG to RGB
     * \param dst               cv::Mat & source and destination, 3 channels,
     *                          in the input moment BRG, at the end of function RGB format
     */
    void bgrToRgb( Mat & dst);

    /*!
     * \brief m_tag             String that indicates the name of the class.
     */
    std::string m_tag;

    /*!
     * \brief m_play            Bool variable used to control the state of the object
     */
    bool m_play;

    /*!
     * \brief m_capture         VideoCapute instance. Inerface between camera hardware and
     *                          application
     */
    VideoCapture m_capture;

    /*!
     * \brief m_playRate        rate used to determine the sleep duration of the Camera's run thread.
     *                          Basically, control the rate rate of data acquisition of the camera.
     */
    int m_playRate;

};

#endif // CAMERA_H
