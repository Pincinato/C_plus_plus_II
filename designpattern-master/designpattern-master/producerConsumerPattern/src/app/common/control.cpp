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

   bool ACK = m_tracking->detectEyes(data->m_frame,faces,eyes);
   if(ACK){
      centerEyes = m_tracking->detectCenter(faces,eyes);
      Point zero(0,0);
      if(centerEyes==zero){ ACK=false;}
      else{m_widget->setPoint(centerEyes);}
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
    return m_tracking->drawEyesCenter(data->m_frame,eyes,centerEyes);
}

void Control::setCamera(const string &option)
{

 cameraOption.clear();
 cameraOption.append(option);
}
