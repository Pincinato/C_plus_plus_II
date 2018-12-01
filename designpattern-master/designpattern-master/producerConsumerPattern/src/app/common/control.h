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
#include "eye_detector.h"
#include "basecamera.h"
#include "basecamerafactory.h"
#include "eyeanalyser.h"

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
    int getDirection(const DataBufferPtr &data,const Point &calibrationLeft,const Point &calibrationRight);
    void clearVectors();
    //Point getEyesCenter();


private:
    IControl* m_widget;
    uint m_height;
    uint m_widht;
    std::string cameraOption;
    std::unique_ptr<BaseCamera> m_player;
    std::unique_ptr<BaseCameraFactory> camera_factory;
    std::unique_ptr<Eye_detector> m_tracking;
    std::shared_ptr<DataBufferPool> m_dataPool;
    std::unique_ptr<QTimer> m_ScanUpdateRateTimer;
    std::unique_ptr<EyeAnalyser> m_analyser;
    std::vector<Rect> eyes;
    std::vector<Rect> faces;
    Point centerEyeLeft;
    Point centerEyeRight;
    deque<cv::Point > EyeRight;
    deque<cv::Point > EyeLeft;
};
#endif // CONTROL_H
