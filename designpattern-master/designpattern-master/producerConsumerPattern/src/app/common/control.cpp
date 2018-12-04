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

Control::Control(IControl *parent) :
    m_widget(parent),
    m_height(256),
    m_widht(256),
    cameraOption("WebCam")
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
    camera_factory.reset(new BaseCameraFactory);
    m_player.reset();;
    m_player = camera_factory->CreateCamera(this,m_dataPool,cameraOption);

    // Message
    m_widget->displayMsg("Control", "Constructed");

    //eye_detector
    m_tracking.reset(new EyeDetector);

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

void Control::setPlayRate(int playRate)
{
    m_player->setPlayRate(playRate);
}

bool Control::getEyes(DataBufferPtr &data){

   bool ACK = m_tracking->detectEyes(data->m_frameGray,m_faces,m_eyes);
   if(ACK){
      m_centerEyeLeft = m_tracking->detectCenterLeftEye(m_faces,m_eyes);
      m_centerEyeRight = m_tracking->detectCenterRightEye(m_faces,m_eyes);
      Point zero(0,0);
      if((m_centerEyeLeft==zero)|| (m_centerEyeRight==zero)){ ACK=false;}
      else{
          m_widget->setPoint(m_centerEyeLeft,m_centerEyeRight);//hmmmm
          m_EyeLeft.push_back(m_centerEyeLeft);
          m_EyeRight.push_back(m_centerEyeRight);
          if(m_EyeLeft.size()>300){ m_EyeLeft.pop_front();}
          if(m_EyeRight.size()>300){m_EyeRight.pop_front();}
      }
   }
   return ACK;
}

bool Control::setEyesInFrame(DataBufferPtr &data){

   return m_tracking->drawEyes(data->m_frame,m_faces,m_eyes);

}

bool Control::setFaceInFrame(DataBufferPtr &data){
    return m_tracking->drawFaces(data->m_frame,m_faces);

}

bool Control::setEyesCenter(DataBufferPtr &data){
   return m_tracking->drawEyesCenter(data->m_frame,m_eyes,m_centerEyeLeft) & (m_tracking->drawEyesCenter(data->m_frame,m_eyes,m_centerEyeRight));

}

void Control::setCamera(const string &option)
{

 cameraOption.clear();
 cameraOption.append(option);
}

void Control::clearVectors(){
    m_EyeLeft.clear();
    m_EyeRight.clear();
}

int Control::getDirection(const DataBufferPtr &data,const Point &calibrationLeft,const Point &calibrationRight,const Mat &Eyetemplate){

    //return m_analyser->getDirection(data->m_frame,calibrationLeft,calibrationRight,EyeLeft,EyeRight,Eyetemplate);
    return m_analyser->getDirection(data->m_frameGray,calibrationLeft,calibrationRight,m_EyeLeft,m_EyeRight,Eyetemplate);

}

int Control::getPosition(const DataBufferPtr &data,const Mat &Templat){

    return m_analyser->getEyePosition(data->m_frame,m_EyeLeft,m_EyeRight,Templat);
}

void Control::setSensibility(int newValue){
    m_analyser->setSensibility(newValue);
}
