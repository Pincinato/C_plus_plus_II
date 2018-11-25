#include "eye_detector.h"

Eye_detector::Eye_detector(Ieye_detector *Owner):m_Owner(Owner){

     m_camera.reset( new Camera( this) );
     if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n");};
     if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading eyes cascade\n");};

}

Eye_detector::~Eye_detector(){

}

void Eye_detector::start(){
    m_camera->start();

}
void Eye_detector::stop(){
    m_camera->stop();
}

void Eye_detector::setData(Mat &frame){

    std::vector<Rect> faces;
    Mat frame_gray;
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
    for( size_t i = 0; i < faces.size(); i++ )
    {
        //Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
        //ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
        Mat faceROI = frame_gray( faces[i] );
        std::vector<Rect> eyes;
        //-- In each face, detect eyes
        eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );
        for( size_t j = 0; j < eyes.size(); j++ )
        {
            Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
            int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
            circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
        }
    }
    //-- Show what you got
    //imshow( "window_name", frame );
    m_Owner->setData(frame);

}

void Eye_detector::setStatus(string cameraStatus){

    m_cameraStatus.clear();
    m_cameraStatus.append(cameraStatus);
}
