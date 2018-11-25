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
// TODO: Remove compile time dependency with observer pattern
// control should compile without including widget.h
//#include "widget.h"
// ------------------------------------------------------------
#include "iwidget.h"

// Forward declarations
class VCamera;
class DataBufferPool;

class Control :  public QWidget , ICamera
{

public:
    Control(IWidget *parent);
    ~Control() override;

    // TODO: Move to interface
    //void displayMsg(const std::string &tag, const std::string &msg) override;
    //void setData(DataBufferPtr dataJunk) override;
    // ------------------------------------------------------------
    void displayMsg(const std::string &tag, const std::string &msg) override;
    void setData(DataBufferPtr dataJunk) override;

    void init();
    void startPlaying();
    void stopPlaying();
    bool isPlaying() const;
    void setPlayRate(int playRate);

private:
    IWidget* m_widget;
    uint m_height;
    uint m_widht;

    std::unique_ptr<VCamera> m_player;
    std::shared_ptr<DataBufferPool> m_dataPool;
    std::unique_ptr<QTimer> m_ScanUpdateRateTimer;
};
#endif // CONTROL_H
