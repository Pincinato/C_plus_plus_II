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
#include <QTimer>
#include "icontrol.h"
#include "basecamerafactory.h"
#include "basecamera.h"

// Forward declarations
class BaseCamera;
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
    void setCamera(const string &option);

private:
    IControl* m_widget;
    uint m_height;
    uint m_widht;
    std::string cameraOption;
    std::unique_ptr<BaseCamera> m_player;
    std::unique_ptr<BaseCameraFactory> camera_factory;
    std::shared_ptr<DataBufferPool> m_dataPool;
    std::unique_ptr<QTimer> m_ScanUpdateRateTimer;

};
#endif // CONTROL_H
