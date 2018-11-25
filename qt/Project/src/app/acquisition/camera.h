#ifndef CAMERA_H
#define CAMERA_H

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "icamera.h"
#include <thread>
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;

class Camera
{
public:
    Camera(Icamera * Owner);
    ~Camera();
    void run();
    void start();
    void stop();
    bool isPlaying();
    bool setConfig();

private:
     unique_ptr<Icamera> m_Owner;
     std::thread cameraThread;
     bool playing;
     VideoCapture capture;

};

#endif // CAMERA_H
