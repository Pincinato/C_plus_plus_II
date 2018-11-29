/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include <memory>
#include "dataBuffer.h"
#include "icontrol.h"
#include <string>

// Forward declarations
class DataBuffer;
class Control;
class VideoVisualizer;
class QTimer;
//class Eye_detector;

namespace Ui {
class Widget;
}

class Widget : public QWidget, IControl
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget() override;
    void displayMsg(const std::string &tag, const std::string &msg) override;
    void setData(DataBufferPtr data) override;
    std::string getCamOption();
    void setPoint(const cv::Point eye_center) override;
private:
    void initGUI();
    void updateScanVis();

private slots:
    void updateGui();
    void updateFrameRate();
    void playDataFromFile();
    void setPlayRate();
    void setCamera(const QString & text);

private:
    Ui::Widget* ui;
    QString m_tag;

    std::shared_ptr<DataBuffer> m_lastData;
    //std::unique_ptr<Control> m_appCtrl;
    std::unique_ptr<Control> m_appCtrl;
    std::unique_ptr<VideoVisualizer> m_videoVisualizer;
    std::unique_ptr<QTimer> m_guiUpdateTimer;
    std::unique_ptr<QTimer> m_frameRateTimer;
    std::string CamOption;
    size_t m_frameCount;
    const size_t m_GuiUpdateRateMS;
    const size_t m_fpsUpdateRateMS;

private slots:

    //void updateFrameEyes();
    void sendBack();

signals:
    //void newFrame();
    void back();

};

#endif // WIDGET_H
