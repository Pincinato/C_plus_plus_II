/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
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

class Control :  public QWidget , ICamera
{

public:
    Control(IControl *parent);
    ~Control() override;

    void displayMsg(const std::string &tag, const std::string &msg) override;
    void setData(DataBufferPtr dataJunk) override;

    void init();
    void startPlaying();
    void stopPlaying();
    bool isPlaying() const;
    void setPlayRate(int playRate);
    bool getEyes(DataBufferPtr &data);
    bool setEyesInFrame(DataBufferPtr &data);
    bool setFaceInFrame(DataBufferPtr &data);
    void setCamera(const string &option);
    bool setEyesCenter(DataBufferPtr &data);
    int getDirection(const DataBufferPtr &data,const Point &calibrationLeft,const Point &calibrationRight,const Mat &Eyetemplate);
    void clearVectors();
    void setSensibility(int newValue);
    int getPosition(const DataBufferPtr &data,const Mat &Templat);
    //Point getEyesCenter();


private:
    IControl* m_widget;
    uint m_height;
    uint m_widht;
    std::string cameraOption;
    std::unique_ptr<BaseCamera> m_player;
    std::unique_ptr<BaseCameraFactory> camera_factory;
    std::unique_ptr<EyeDetector> m_tracking;
    std::shared_ptr<DataBufferPool> m_dataPool;
    std::unique_ptr<QTimer> m_ScanUpdateRateTimer;
    std::unique_ptr<EyeAnalyser> m_analyser;
    std::vector<Rect> m_eyes;
    std::vector<Rect> m_faces;
    Point m_centerEyeLeft;
    Point m_centerEyeRight;
    deque<cv::Point > m_EyeRight;
    deque<cv::Point > m_EyeLeft;
};
#endif // CONTROL_H
