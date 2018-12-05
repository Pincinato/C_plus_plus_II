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
    cascade=true;
    if( !m_face_cascade.load( m_face_cascade_name ) ) {cascade=false;}
    if( !m_eyes_cascade.load( m_eyes_cascade_name ) ) {cascade=false;}

}

EyeDetector::~EyeDetector()
{

}

bool EyeDetector::detectEyes(const Mat &frame,vector<Rect> &faces,vector<Rect> &eyes){

    bool ACK=false;
    faces.clear();
    eyes.clear();
    if(cascade){
        if(!frame.empty()){
            equalizeHist( frame, frame );
            m_face_cascade.detectMultiScale( frame, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
            for_each(faces.begin(),faces.end(),[&](Rect face){
                Mat faceROI = frame(face);
                m_eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );
                if(eyes.size()>0){
                    ACK=true;
                }
            });
        }
    }
    return ACK;

}

bool EyeDetector::drawEyes( Mat &frame,const vector<Rect> &faces,const  vector<Rect> &eyes){

    bool ACK=false;
    if((faces.size()>0) &(eyes.size()>0)){
        for_each(faces.cbegin(),faces.cend(),[&](Rect face){
            for_each(eyes.cbegin(),eyes.cend(),[&](Rect eye){
               Point eye_center( face.x + eye.x + eye.width/2, face.y + eye.y + eye.height/2 );
               int radius = cvRound( (eye.width + eye.height)*0.25 );
               circle(frame, eye_center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
            });
        });
        ACK=true;
    }
    return ACK;

}

bool EyeDetector::drawFaces(Mat &frame,const vector<Rect> &faces){

    bool ACK=false;
    if(faces.size()>0){
        for_each(faces.cbegin(),faces.cend(),[&](Rect face){
            Point center( face.x +face.width/2,face.y + face.height/2 );
            ellipse( frame, center, Size( face.width/2, face.height/2), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
        });
        ACK=true;
    }
    return ACK;
}

Point EyeDetector::detectCenterRightEye(const vector<Rect> &faces,const vector<Rect> &eyes){

    Point ret(0,0);
    if (eyes.size()>1){
        Rect rightEye=getRightEye(eyes);
        Point eye_center( faces[0].x + rightEye.x + rightEye.width/2, faces[0].y + rightEye.y + rightEye.height/2 );
        return eye_center;
     }
    return ret;
}

Point EyeDetector::detectCenterLeftEye(const vector<Rect> &faces,const vector<Rect> &eyes){

    Point ret(0,0);
    if (eyes.size()>1){
        Rect leftEye=getLeftEye(eyes);
        Point eye_center( faces[0].x + leftEye.x + leftEye.width/2, faces[0].y + leftEye.y + leftEye.height/2 );
        return eye_center;
     }
    return ret;
}

bool EyeDetector::drawBothCenterEye(const vector<Rect> &faces,const  vector<Rect> &eyes){
    bool ACK=false;
    for_each(faces.cbegin(),faces.cend(),[&] (Rect face){
        for_each(eyes.cbegin(),eyes.cend(),[&](Rect eye){
            Point eye_center( face.x + eye.x + eye.width/2, face.y + eye.y + eye.height/2 );
            ACK=true;
        });});

    return ACK;
}

bool EyeDetector::drawEyesCenter(Mat &frame,const Point & eye_center){

    bool ACK=false;
    circle(frame, eye_center, 1, Scalar( 255, 0, 0 ), 2, 8, 0 );
    ACK=true;
    return ACK;
}


Rect EyeDetector::getRightEye(const vector<Rect> &eyes){

    auto itr = max_element(eyes.begin(),eyes.end(),[](Rect a, Rect b){
       return a.tl().x < b.tl().x;
    });
    return *itr;
}

Rect EyeDetector::getLeftEye(const vector<Rect> &eyes){

    auto itr = min_element(eyes.begin(),eyes.end(),[](Rect a, Rect b){
       return a.tl().x < b.tl().x;
    });
    return *itr;
}

bool EyeDetector::cascadeIsLoaded(){
    return cascade;
}
