#include "camera.h"

Camera::Camera(Icamera *Owner):m_Owner(Owner),playing(false)
{
     m_Owner->setStatus("Camera was created");
}
Camera::~Camera(){
    playing = false;
    if(cameraThread.joinable())
    {
        cameraThread.join();
    }
    if(capture.isOpened()){
        capture.release();
    }
     m_Owner->setStatus("Camera was destroyed");
}

void Camera::run(){
    Mat frame;
    if(capture.isOpened()){
        m_Owner->setStatus("Start Playing");
        while((playing) & (capture.read(frame))){
            if(frame.empty()){ m_Owner->setStatus("No captured frame");}
            else{m_Owner->setData(frame);}
            int sleeptime = static_cast<int>( 1000.0f/3) ;
            std::this_thread::sleep_for( std::chrono::milliseconds( sleeptime ));
        }
    }
    else { m_Owner->setStatus("Unable to Open camera");}
}

void Camera::start(){

    capture.open(0);
    playing = true;
    //cameraThread = std::thread(&Camera::run, this);
    //run();
}

void Camera::stop(){
    playing = false;
    m_Owner->setStatus("Camera was stoped");
    if(capture.isOpened()){
        capture.release();
    }
}

bool Camera::isPlaying(){
    return playing;
}
