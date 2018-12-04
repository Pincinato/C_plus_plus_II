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
#include "eye_detector.h"

Control::Control(IControl *parent) :
    m_widget(parent),
    m_height(256),
    m_widht(256),
    cameraOption("WebCam")
{
    faces.clear();
    eyes.clear();
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
    m_player.reset();
    m_player = camera_factory->CreateCamera(this,m_dataPool,cameraOption);

    // Message
    m_widget->displayMsg("Control", "Constructed");

    //eye_detector
    m_tracking.reset(new Eye_detector);

    //eye_analyser
    m_analyser.reset(new EyeAnalyser);

    //vector init.
    EyeRight.clear();
    EyeLeft.clear();
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

   bool ACK = m_tracking->detectEyes(data->m_frameGray,faces,eyes);
   if(ACK){
      centerEyeLeft = m_tracking->detectCenterLeftEye(faces,eyes);
      centerEyeRight = m_tracking->detectCenterRightEye(faces,eyes);
      Point zero(0,0);
      if((centerEyeLeft==zero)|| (centerEyeRight==zero)){ ACK=false;}
      else{
          m_widget->setPoint(centerEyeLeft,centerEyeRight);//hmmmm
          EyeLeft.push_back(centerEyeLeft);
          EyeRight.push_back(centerEyeRight);
          if(EyeLeft.size()>300){ EyeLeft.pop_front();}
          if(EyeRight.size()>300){EyeRight.pop_front();}
      }
   }
   return ACK;
}

bool Control::setEyesInFrame(DataBufferPtr &data){

   return m_tracking->drawEyes(data->m_frame,faces,eyes);

}

bool Control::setFaceInFrame(DataBufferPtr &data){
    return m_tracking->drawFaces(data->m_frame,faces);

}

bool Control::setEyesCenter(DataBufferPtr &data){
   return m_tracking->drawEyesCenter(data->m_frame,eyes,centerEyeLeft) & (m_tracking->drawEyesCenter(data->m_frame,eyes,centerEyeRight));

}

void Control::setCamera(const string &option)
{

 cameraOption.clear();
 cameraOption.append(option);
}

void Control::clearVectors(){
    EyeLeft.clear();
    EyeRight.clear();
}

int Control::getDirection(const DataBufferPtr &data,const Point &calibrationLeft,const Point &calibrationRight,const Mat &Eyetemplate){

    //return m_analyser->getDirection(data->m_frame,calibrationLeft,calibrationRight,EyeLeft,EyeRight,Eyetemplate);
    return m_analyser->getDirection(data->m_frameGray,calibrationLeft,calibrationRight,EyeLeft,EyeRight,Eyetemplate);

}

int Control::getPosition(const DataBufferPtr &data,const Mat &Templat){

    return m_analyser->getEyePosition(data->m_frame,EyeLeft,EyeRight,Templat);
}

void Control::setSensibility(int newValue){
    m_analyser->setSensibility(newValue);
}
