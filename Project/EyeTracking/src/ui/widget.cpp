/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#include <iostream>
#include <sstream>

#include <QCameraInfo>
#include <QCamera>
#include <QWidget>
#include "icontrol.h"
#include "widget.h"
#include "ui_widget.h"
#include "dataBuffer.h"
#include "control.h"
#include "videoVisualizer.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    m_tag("Widget"),
    m_CamOption("WebCam"),
    m_frameCount(0),
    m_GuiUpdateRateMS(20),
    m_fpsUpdateRateMS(500)
{    
    ui->setupUi(this);

    // Setup main control - passing widget to control
    m_appCtrl.reset( new Control(this) );
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
    m_guiUpdateTimer->start(static_cast<const int>(m_GuiUpdateRateMS));

    // Frame Rate-timer
    m_frameRateTimer.reset( new QTimer(this));
    connect( m_frameRateTimer.get(), SIGNAL(timeout()), this, SLOT(updateFrameRate()) );
    m_frameRateTimer->start(static_cast<const int>(m_fpsUpdateRateMS));

    //back button
    connect(ui->back_pushButton,SIGNAL(clicked()),this,SLOT(sendBack()));
    //index camera
    connect(ui->CameraOption,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(setCamera(const QString &)));

    //Detecting cameras availables
    m_numberOfActualCamera=static_cast<uint>(QCameraInfo::availableCameras().count());
   if(m_numberOfActualCamera>= 1){
       ui->CameraOption->addItem("WebCam"); //WebCam;
   }
   if(m_numberOfActualCamera>= 2){
        ui->CameraOption->addItem("USBCamera");//USBCamera
   }

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
    size_t numberCamera= static_cast<uint>(QCameraInfo::availableCameras().count());
    if( m_lastData )
    {
        m_appCtrl->getEyes(m_lastData);
        m_appCtrl->setEyesInFrame(m_lastData);
        m_appCtrl->setEyesCenter(m_lastData);
        if((m_appCtrl->isPlaying()) && (m_appCtrl->isDetecting()) && (m_numberOfActualCamera == numberCamera)){
            m_videoVisualizer->setScan(m_lastData);
        }
        if(m_appCtrl->isPlaying()==false){
            m_appCtrl->stopDetecting();
        }
    }
    updateCameraOptions(numberCamera);
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
        m_appCtrl->startDetecting();
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
    float fps = static_cast<float>(m_frameCount / m_fpsUpdateRateMS * 1000.f);
    ui->frameRate_label->setText("FPS: " + QString::number(static_cast<double>(fps)));
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

void Widget::setCamera(const QString &text){

    if( m_appCtrl->isPlaying() )
    {
        m_appCtrl->stopPlaying();
        ui->play_pushButton->setText("Play");
    }
    m_CamOption.clear();
    m_CamOption.append(text.toUtf8().constData());
    m_appCtrl->setCamera(text.toUtf8().constData());
}

string Widget::getCamOption(){
    return m_CamOption;
}


void Widget::setPoint(const cv::Point &eyeLeft,const cv::Point &eyeRight){
    cv::Point a,b;
    a=eyeLeft;
    b=eyeRight;
}

void Widget::myShow(){
    showFullScreen();
}

void Widget::updateCameraOptions(const size_t &numberCamera){

    if(m_numberOfActualCamera > numberCamera){  //Camera waas removed.
        if(numberCamera<2){
            ui->CameraOption->removeItem(1);
        }
        if(numberCamera<1){
            ui->CameraOption->removeItem(0);
        }
    }
    else if (m_numberOfActualCamera < numberCamera){
        if(numberCamera>1){
            ui->CameraOption->addItem("USBCamera");
        }
    }
    m_numberOfActualCamera = numberCamera;
}
