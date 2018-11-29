/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#include <iostream>
#include <sstream>

#include "widget.h"
#include "ui_widget.h"
#include "dataBuffer.h"
#include "control.h"
#include "videoVisualizer.h"
//#include "eye_detector.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    m_tag("Widget"),
    CamOption("WebCam"),
    m_frameCount(0),
    m_GuiUpdateRateMS(50),
    m_fpsUpdateRateMS(500)
{    
    ui->setupUi(this);

    // Setup main control - passing widget to control
    m_appCtrl.reset( new Control(this) );
    //m_appCtrl.reset(new Eye_detector(this));
    // reset data container
    m_lastData.reset();

    // setup GUI
    initGUI();

    // Connect GUI
    connect(ui->play_pushButton, SIGNAL(clicked()), this, SLOT(playDataFromFile()));
    connect(ui->frameRateSlider, SIGNAL(valueChanged(int)), this, SLOT(setPlayRate()));

    // Update GUI-timer to update images etc. every 20 ms
    m_guiUpdateTimer.reset( new QTimer(this));
    connect( m_guiUpdateTimer.get(), SIGNAL(timeout()), this, SLOT(updateGui()) );
    m_guiUpdateTimer->start(m_GuiUpdateRateMS);

    // Frame Rate-timer
    m_frameRateTimer.reset( new QTimer(this));
    connect( m_frameRateTimer.get(), SIGNAL(timeout()), this, SLOT(updateFrameRate()) );
    m_frameRateTimer->start(m_fpsUpdateRateMS);

    //back button
    connect(ui->back_pushButton,SIGNAL(clicked()),this,SLOT(sendBack()));
    //newFrame signal
    //connect(this,SIGNAL(newFrame()),this,SLOT(updateFrameEyes()));
    //connect qcombobox
    connect(ui->CameraOption,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(setCamera(const QString &)));


}

Widget::~Widget()
{

}

// -----------------------------------------------------------------
// Functions called by Control (tight coupling)
// -----------------------------------------------------------------
void Widget::displayMsg(const std::string &tag, const std::string &msg)
{
    std::cout << " Info: " << tag << " : " <<  msg << std::endl;
}

void Widget::setData(DataBufferPtr data)
{
    m_lastData = data;
    ++m_frameCount;
    //emit newFrame();
}

// -----------------------------------------------------------------
// GUI
// -----------------------------------------------------------------
void Widget::initGUI()
{
    // Player Widget
    m_videoVisualizer.reset( new VideoVisualizer(ui->videoWidgetHolder) );

    // Frame Rate Slides
    ui->frameRateSlider->setMaximum(80);
    ui->frameRateSlider->setMinimum(1);
    ui->frameRateSlider->setValue(33);
}

// Called by GUI-timer
void Widget::updateGui()
{
    if( m_lastData )
    {
        m_appCtrl->getEyes(m_lastData);
        m_appCtrl->setEyesInFrame(m_lastData);
        //m_appCtrl->setFaceInFrame(m_lastData);
        m_appCtrl->setEyesCenter(m_lastData);
        m_videoVisualizer->setScan(m_lastData);
    }
}

void Widget::playDataFromFile()
{
    if( m_appCtrl->isPlaying() )
    {
        m_appCtrl->stopPlaying();
        ui->play_pushButton->setText("Play");
    }
    else
    {
        m_appCtrl->startPlaying();
        ui->play_pushButton->setText("Stop");
    }
}

void Widget::setPlayRate()
{
    int playRate = ui->frameRateSlider->value();
    m_appCtrl->setPlayRate(playRate);
}

void Widget::updateFrameRate()
{
    float fps = (float)m_frameCount / m_fpsUpdateRateMS * 1000.f;
    ui->frameRate_label->setText("FPS: " + QString::number(fps));
    m_frameCount = 0;
}

void Widget::sendBack(){

    if( m_appCtrl->isPlaying() )
    {
        m_appCtrl->stopPlaying();
        ui->play_pushButton->setText("Play");
    }
    emit back();
}

/*
void Widget::updateFrameEyes(){

    if( m_lastData )
    {
        m_appCtrl->getEyes(m_lastData);
        m_appCtrl->setEyesInFrame(m_lastData);
    }
}
*/

void Widget::setCamera(const QString &text){

    if( m_appCtrl->isPlaying() )
    {
        m_appCtrl->stopPlaying();
        ui->play_pushButton->setText("Play");
    }
    CamOption.clear();
    CamOption.append(text.toUtf8().constData());
    m_appCtrl->setCamera(text.toUtf8().constData());
}

string Widget::getCamOption(){
    return CamOption;
}

void Widget::setPoint(const cv::Point eye_center){
    cv::Point a;
    a=eye_center;
}
