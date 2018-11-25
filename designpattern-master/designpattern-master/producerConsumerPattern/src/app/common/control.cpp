/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#include "control.h"
#include "VCamera.h"
#include "dataBufferPool.h"

Control::Control(IWidget *parent) :
    m_widget(parent),
    m_height(256),
    m_widht(256)
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
    m_player.reset( new VCamera( this, m_dataPool) );

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

    return m_tracking->detectEyes(data->m_frame,faces,eyes);
}

bool Control::setEyesInFrame(DataBufferPtr &data){

    return m_tracking->drawEyes(data->m_frame,faces,eyes);
}

bool Control::setFaceInFrame(DataBufferPtr &data){
    return m_tracking->drawFaces(data->m_frame,faces);
}
