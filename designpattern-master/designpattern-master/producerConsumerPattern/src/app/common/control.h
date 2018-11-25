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
#include "iwidget.h"
#include "eye_detector.h"

using namespace cv;
// Forward declarations
class VCamera;
class DataBufferPool;

class Control :  public QWidget , ICamera
{

public:
    Control(IWidget *parent);
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

private:
    IWidget* m_widget;
    uint m_height;
    uint m_widht;
    std::unique_ptr<Eye_detector> m_tracking;
    std::unique_ptr<VCamera> m_player;
    std::shared_ptr<DataBufferPool> m_dataPool;
    std::unique_ptr<QTimer> m_ScanUpdateRateTimer;
    std::vector<Rect> eyes;
    std::vector<Rect> faces;
};
#endif // CONTROL_H
