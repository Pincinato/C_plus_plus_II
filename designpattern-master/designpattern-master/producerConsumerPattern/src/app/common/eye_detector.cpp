/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#include "Eye_detector.h"
#include "VCamera.h"
#include "dataBufferPool.h"

Eye_detector::Eye_detector() :
    face_cascade_name("haarcascade_frontalface_alt.xml"),
    eyes_cascade_name("haarcascade_eye_tree_eyeglasses.xml")
{

    if( !face_cascade.load( face_cascade_name ) ) { printf("--(!)Error loading face cascade\n");}
    else printf("Everything Ok \n");
    if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading eyes cascade\n");}
    else printf("Everything Ok \n");

}

Eye_detector::~Eye_detector()
{

}

bool Eye_detector::detectEyes(const Mat &frame,vector<Rect> &faces,vector<Rect> &eyes){

    bool ACK=false;
    Mat frame_gray;
    faces.clear();
    eyes.clear();
    if(!frame.empty()){
        cvtColor(frame, frame_gray, COLOR_BGR2GRAY );
        equalizeHist( frame_gray, frame_gray );
        face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
        for( size_t i = 0; i < faces.size(); i++ )
        {
            Mat faceROI = frame_gray( faces[i] );
            eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );
            if(eyes.size()>0){
               ACK=true;
            }
        }
    }
    return ACK;

}

bool Eye_detector::drawEyes( Mat &frame,std::vector<Rect> &faces, vector<Rect> &eyes){

    bool ACK=false;
    if((faces.size()>0) &(eyes.size()>0)){
        for( size_t i = 0; i < faces.size(); i++ )
        {
            for( size_t j = 0; j < eyes.size(); j++ )
            {
              Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
              int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
             circle(frame, eye_center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
            }
        }
        ACK=true;
    }
    return ACK;

}

bool Eye_detector::drawFaces(Mat &frame,vector<Rect> &faces){

    bool ACK=false;
    if(faces.size()>0){
        for( size_t i = 0; i < faces.size(); i++ )
        {
            Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
            ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
        }
        ACK=true;
    }
    return ACK;
}

Point Eye_detector::detectCenter(std::vector<Rect> &faces, vector<Rect> &eyes){

    Point ret(0,0);
    for( size_t i = 0; i < faces.size(); i++ )
    {
        for( size_t j = 0; j < eyes.size(); j++ )
        {
            Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            return eye_center;
        }
    }
    return ret;
}

bool Eye_detector::drawBothCenterEye(std::vector<Rect> &faces, vector<Rect> &eyes){
    bool ACK=false;
    for( size_t i = 0; i < faces.size(); i++ )
    {
        for( size_t j = 0; j < eyes.size(); j++ )
        {
            Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            ACK=true;
        }
    }
    return ACK;
}

bool Eye_detector::drawEyesCenter(Mat &frame, vector<Rect> &eyes,Point & eye_center){

    bool ACK=false;
    for( size_t j = 0; j < eyes.size(); j++ )
    {
        circle(frame, eye_center, 1, Scalar( 255, 0, 0 ), 2, 8, 0 );
        ACK=true;
    }
    return ACK;
}


Rect Eye_detector::getRightEye(vector<Rect> &eyes){

       int rightEyeValue = 0;
      int rightEyeIndex = 0;
      for (uint i = 0; i < eyes.size(); i++)
      {
          if (eyes[i].tl().x > rightEyeValue)
          {
              rightEyeValue = eyes[i].tl().x;
              rightEyeIndex = i;
          }
      }
      return eyes[rightEyeIndex];

}


