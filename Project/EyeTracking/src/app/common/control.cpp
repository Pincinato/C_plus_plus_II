/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#include "control.h"
#include "icontrol.h"
#include "VCamera.h"
#include "dataBufferPool.h"
#include "memory.h"
#include <QTimer>
#include "eyeDetector.h"
#include "basecamera.h"
#include "basecamerafactory.h"
#include "eyeAnalyser.h"

Control::Control(IControl *parent) :
    m_widget(parent),
    m_height(256),
    m_widht(256),
    m_cameraOption("WebCam"),
    m_detecting(true)
{
    m_faces.clear();
    m_eyes.clear();
    // init control handels
    init();
}

Control::~Control()
{

}

// reset main handels
void Control::init()
{
    // init data pool
    m_dataPool.reset(new DataBufferPool(m_height, m_widht));

    // create file reader
    m_camera_factory.reset(new BaseCameraFactory);
    m_player.reset();;
    m_player = m_camera_factory->CreateCamera(this,m_dataPool,m_cameraOption);

    // Message
    m_widget->displayMsg("Control", "Constructed");

    //eye_detector
    m_tracking.reset(new EyeDetector);
    if(!m_tracking->cascadeIsLoaded()){ m_widget->displayMsg("EyeDetector", "Cascade's files not found");}
    //eye_analyser
    m_analyser.reset(new EyeAnalyser);
    //vector init.
    m_EyeRight.clear();
    m_EyeLeft.clear();
}

// -----------------------------------------------------------------
// Functions called by Player (tight coupling)
// -----------------------------------------------------------------
void Control::displayMsg(const std::string &tag, const std::string &msg)
{    
    m_widget->displayMsg(tag, msg);
}

void Control::setData(DataBufferPtr dataJunk)
{
    m_widget->setData(dataJunk);
}

void Control::startPlaying()
{
    init(); // reinit handlers
    m_player->startPlayData();
}

void Control::stopPlaying()
{
    m_player->stop();
}

bool Control::isPlaying() const
{
    bool isPlaying = (m_player->isPlaying());
    return isPlaying;
}

void Control::setPlayRate(const int &playRate)
{
    m_player->setPlayRate(playRate);
}

bool Control::getEyes(const DataBufferPtr &data){

   bool ACK = false;
   if(isPlaying()){
       const uint8_t maxDequeSize=100;
       ACK = m_tracking->detectEyes(data->m_frameGray,m_faces,m_eyes);
       if(ACK){
            m_centerEyeLeft = m_tracking->detectCenterLeftEye(m_faces,m_eyes);
            m_centerEyeRight = m_tracking->detectCenterRightEye(m_faces,m_eyes);
            Point zero(0,0);
            if((m_centerEyeLeft==zero)|| (m_centerEyeRight==zero)){ ACK=false;}
            else{
                m_widget->setPoint(m_centerEyeLeft,m_centerEyeRight);
                m_EyeLeft.push_back(m_centerEyeLeft);
                m_EyeRight.push_back(m_centerEyeRight);
                if(m_EyeLeft.size()>maxDequeSize){ m_EyeLeft.pop_front();}
                if(m_EyeRight.size()>maxDequeSize){m_EyeRight.pop_front();}
            }
        }
   }
   return ACK;
}

bool Control::setEyesInFrame(DataBufferPtr &data){

   bool ACK= false;
   if(isDetecting()){
   ACK =  m_tracking->drawEyes(data->m_frame,m_faces,m_eyes);
   }
   return ACK;
}

bool Control::setFaceInFrame(DataBufferPtr &data){
    bool ACK= false;
    if(isDetecting()){
       ACK=  m_tracking->drawFaces(data->m_frame,m_faces);
    }
    return ACK;

}

bool Control::setEyesCenter(DataBufferPtr &data){
    bool ACK= false;
    if(isDetecting()){
        ACK=  m_tracking->drawEyesCenter(data->m_frame,m_centerEyeLeft) & (m_tracking->drawEyesCenter(data->m_frame,m_centerEyeRight));
    }
    return ACK;

}

void Control::setCamera(const string &option)
{

 m_cameraOption.clear();
 m_cameraOption.append(option);
}

void Control::clearVectors(){
    m_EyeLeft.clear();
    m_EyeRight.clear();
}

short Control::getDirection(const Point &calibrationLeft,const Point &calibrationRight){

    return m_analyser->getDirection(calibrationLeft,calibrationRight,m_EyeLeft,m_EyeRight);

}

void Control::startDetecting(){
    m_detecting=true;
}

void Control::stopDetecting(){
    m_detecting=false;
}

bool Control::isDetecting() const {
    return m_detecting;
}


void Control::setSensibility(const int &newValue){
    m_analyser->setSensibility(newValue);
}
