/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#include "eyeDetector.h"
#include "VCamera.h"
#include "dataBufferPool.h"

EyeDetector::EyeDetector() :
    m_face_cascade_name("haarcascade_frontalface_alt.xml"),
    m_eyes_cascade_name("haarcascade_eye_tree_eyeglasses.xml")
{

    if( !m_face_cascade.load( m_face_cascade_name ) ) { printf("--(!)Error loading face cascade\n");}
    else printf("Everything Ok \n");
    if( !m_eyes_cascade.load( m_eyes_cascade_name ) ){ printf("--(!)Error loading eyes cascade\n");}
    else printf("Everything Ok \n");

}

EyeDetector::~EyeDetector()
{

}

bool EyeDetector::detectEyes(const Mat &frame,vector<Rect> &faces,vector<Rect> &eyes){

    bool ACK=false;
    faces.clear();
    eyes.clear();
    if(!frame.empty()){
        equalizeHist( frame, frame );
        m_face_cascade.detectMultiScale( frame, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
        for( size_t i = 0; i < faces.size(); ++i )
        {
            Mat faceROI = frame( faces[i] );
            m_eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );
            if(eyes.size()>0){
               ACK=true;
            }
        }
    }
    return ACK;

}

bool EyeDetector::drawEyes( Mat &frame,std::vector<Rect> &faces, vector<Rect> &eyes){

    bool ACK=false;
    if((faces.size()>0) &(eyes.size()>0)){
        for( size_t i = 0; i < faces.size(); ++i )
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

bool EyeDetector::drawFaces(Mat &frame,vector<Rect> &faces){

    bool ACK=false;
    if(faces.size()>0){
        for( size_t i = 0; i < faces.size(); ++i )
        {
            Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
            ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
        }
        ACK=true;
    }
    return ACK;
}

Point EyeDetector::detectCenterRightEye(std::vector<Rect> &faces, vector<Rect> &eyes){

    Point ret(0,0);
    if (eyes.size()>1){
        Rect rightEye=getRightEye(eyes);
        Point eye_center( faces[0].x + rightEye.x + rightEye.width/2, faces[0].y + rightEye.y + rightEye.height/2 );
        return eye_center;
     }
    return ret;
}

Point EyeDetector::detectCenterLeftEye(std::vector<Rect> &faces, vector<Rect> &eyes){

    Point ret(0,0);
    if (eyes.size()>1){
        Rect leftEye=getLeftEye(eyes);
        Point eye_center( faces[0].x + leftEye.x + leftEye.width/2, faces[0].y + leftEye.y + leftEye.height/2 );
        return eye_center;
     }
    return ret;
}

bool EyeDetector::drawBothCenterEye(std::vector<Rect> &faces, vector<Rect> &eyes){
    bool ACK=false;
    for( size_t i = 0; i < faces.size(); ++i )
    {
        for( size_t j = 0; j < eyes.size(); j++ )
        {
            Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            ACK=true;
        }
    }
    return ACK;
}

bool EyeDetector::drawEyesCenter(Mat &frame, vector<Rect> &eyes,Point & eye_center){

    bool ACK=false;
    for( size_t j = 0; j < eyes.size(); j++ )
    {
        circle(frame, eye_center, 1, Scalar( 255, 0, 0 ), 2, 8, 0 );
        ACK=true;
    }
    return ACK;
}


Rect EyeDetector::getRightEye(vector<Rect> &eyes){

       int rightEyeValue = 0;
      int rightEyeIndex = 0;
      for (uint i = 0; i < eyes.size(); ++i)
      {
          if (eyes[i].tl().x > rightEyeValue)
          {
              rightEyeValue = eyes[i].tl().x;
              rightEyeIndex = i;
          }
      }
      return eyes[rightEyeIndex];
}

Rect EyeDetector::getLeftEye(vector<Rect> &eyes){

      int leftEyeValue =99999;
      int leftEyeIndex = 0;
      for (uint i = 0; i < eyes.size(); ++i)
      {
          if (eyes[i].tl().x < leftEyeValue)
          {
              leftEyeValue = eyes[i].tl().x;
              leftEyeIndex = i;
          }
      }
      return eyes[leftEyeIndex];
}