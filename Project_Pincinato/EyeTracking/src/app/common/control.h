/****************************************************************************
** Copyright (c) 2018 University of Bern & Bern University of Applied Science
** Project: Eye tracking
** Done by: Pratick Arnold , Modified by : Thiago Pincinato
** Contact:  Thiago Henrique Pincianto ( thiago.pincinato@bfh.ch )
*****************************************************************************/
#ifndef CONTROL_H
#define CONTROL_H

#include <QWidget>
#include <memory>
#include "icamera.h"
#include "icontrol.h"
#include <QTimer>
#include "eyeDetector.h"
#include "basecamera.h"
#include "basecamerafactory.h"
#include "eyeAnalyser.h"

using namespace cv;
// Forward declarations
class VCamera;
class DataBufferPool;

/*!
 * \brief The Control class
 */
class Control :  public QWidget , ICamera
{

public:
    /*!
     * \brief Control
     * \param parent
     */
    Control(IControl *parent);
    ~Control() override;

    /*!
     * \brief displayMsg
     * \param tag
     * \param msg
     */
    void displayMsg(const std::string &tag, const std::string &msg) override;

    /*!
     * \brief setData
     * \param dataJunk
     */
    void setData(DataBufferPtr dataJunk) override;

    /*!
     * \brief init
     */
    void init();

    /*!
     * \brief startPlaying
     */
    void startPlaying();

    /*!
     * \brief stopPlaying
     */
    void stopPlaying();

    /*!
     * \brief isPlaying
     * \return
     */
    bool isPlaying() const;

    /*!
     * \brief setPlayRate
     * \param playRate
     */
    void setPlayRate(int playRate);

    /*!
     * \brief getEyes
     * \param data
     * \return
     */
    bool getEyes(DataBufferPtr &data);

    /*!
     * \brief setEyesInFrame
     * \param data
     * \return
     */
    bool setEyesInFrame(DataBufferPtr &data);

    /*!
     * \brief setFaceInFrame
     * \param data
     * \return
     */
    bool setFaceInFrame(DataBufferPtr &data);

    /*!
     * \brief setCamera
     * \param option
     */
    void setCamera(const string &option);

    /*!
     * \brief setEyesCenter
     * \param data
     * \return
     */
    bool setEyesCenter(DataBufferPtr &data);

    /*!
     * \brief getDirection
     * \param calibrationLeft
     * \param calibrationRight
     * \return
     */
    int getDirection(const Point &calibrationLeft,const Point &calibrationRight);

    /*!
     * \brief clearVectors
     */
    void clearVectors();

    /*!
     * \brief setSensibility
     * \param newValue
     */
    void setSensibility(int newValue);
    //Point getEyesCenter();


private:
    /*!
     * \brief m_widget
     */
    IControl* m_widget;

    /*!
     * \brief m_height
     */
    uint m_height;

    /*!
     * \brief m_widht
     */
    uint m_widht;

    /*!
     * \brief cameraOption
     */
    std::string cameraOption;

    /*!
     * \brief m_player
     */
    std::unique_ptr<BaseCamera> m_player;

    /*!
     * \brief camera_factory
     */
    std::unique_ptr<BaseCameraFactory> camera_factory;

    /*!
     * \brief m_tracking
     */
    std::unique_ptr<EyeDetector> m_tracking;

    /*!
     * \brief m_dataPool
     */
    std::shared_ptr<DataBufferPool> m_dataPool;

    /*!
     * \brief m_ScanUpdateRateTimer
     */
    std::unique_ptr<QTimer> m_ScanUpdateRateTimer;

    /*!
     * \brief m_analyser
     */
    std::unique_ptr<EyeAnalyser> m_analyser;

    /*!
     * \brief m_eyes
     */
    std::vector<Rect> m_eyes;

    /*!
     * \brief m_faces
     */
    std::vector<Rect> m_faces;

    /*!
     * \brief m_centerEyeLeft
     */
    Point m_centerEyeLeft;

    /*!
     * \brief m_centerEyeRight
     */
    Point m_centerEyeRight;

    /*!
     * \brief m_EyeRight
     */
    deque<cv::Point > m_EyeRight;

    /*!
     * \brief m_EyeLeft
     */
    deque<cv::Point > m_EyeLeft;
};
#endif // CONTROL_H
