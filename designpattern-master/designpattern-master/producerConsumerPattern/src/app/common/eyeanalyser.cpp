#include "eyeanalyser.h"

#include <QWidget>
#include "icontrol.h"
#include "control.h"
#include <string>
using namespace std;

EyeAnalyser::EyeAnalyser()
{
    sensibility=10;
}


short EyeAnalyser::getEyePosition(const Mat &frame,const deque<Point> &leftEye,const deque<Point> &rightEye){

    Point leftAverage = averagePoint(leftEye);
    Point rightAverage= averagePoint(rightEye);
    int width = (static_cast<int>(static_cast<float>((rightAverage.x-leftAverage.x)*0.4)));//0.8// need to check!!!
    int height= static_cast<int>(width*0.6);//0.3//radio  ~0.4


    /*
    //Setting mask of whole left eye
    Rect Left(leftAverage.x-width/2,leftAverage.y-height/2,width,height);
    Mat imageGray=frame(Left);
    cvtColor(imageGray,imageGray,COLOR_BGR2GRAY );
    //getting left eye
    Mat image=frame(Left);
    equalizeHist(imageGray, imageGray);
    //medianBlur(imageGray, imageGray,3);
    vector<Vec3f> circles;
    HoughCircles( imageGray, circles, CV_HOUGH_GRADIENT, 1, 30, 250, 25, 0, 0);
    for( size_t i = 0; i < circles.size(); i++ )
    {
       Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
       int radius = cvRound(circles[i][2]);
       // circle center
       circle( imageGray, center, 3, 255, 2, 8, 0 );
       // circle outline
       circle( imageGray, center, radius, 255, 3, 8, 0 );
     }
    imshow("circles in eyes",imageGray);
    */

    /*
    //Setting mask of each part of the eye
    Rect Left(leftAverage.x-width/2,leftAverage.y-height/2,width/2,height);
    Rect Right(leftAverage.x,leftAverage.y-height/2,width/2,height);
    Rect Up(leftAverage.x-width/2,leftAverage.y-height/2,width,height/2);
    Rect Down(leftAverage.x-width/2,leftAverage.y,width,height/2);
    Mat leftImage = frame(Left);
    imshow("left",leftImage);
    Mat rightImage = frame(Right);
    imshow("Rigth",rightImage);
    Mat upImage = frame(Up);
    imshow("Up",upImage);
    Mat downImage = frame(Down);
    imshow("Down",downImage);
    float leftSum =getSumPixel (leftImage);
    float rightSum =getSumPixel (rightImage);
    float upSum =getSumPixel(upImage);
    float downSum =getSumPixel(downImage);
    LeftRight( leftSum, rightSum);
    UpDown( upSum,  downSum);
    */

    return 0;

}


short EyeAnalyser::getDirection(const Mat &frame,const Point &calibrationLeft,const Point &calibrationRight,const deque<Point> &leftEye,const deque<Point> &rightEye){

     getEyePosition(frame,leftEye,rightEye);
     return getDistance(calibrationLeft,leftEye);

}

Point EyeAnalyser::averagePoint(const deque<Point> &vec){

    Point sum(0,0);
    for(auto const &it : vec){
        sum.x+=it.x;
        sum.y+=it.y;
    }
    sum.x/=vec.size();
    sum.y/=vec.size();
    return sum;
}

float EyeAnalyser::getSumPixel(const Mat &Image){

       Mat imageGray;
       cvtColor(Image,imageGray,COLOR_BGR2GRAY );
       equalizeHist( imageGray, imageGray );
       return static_cast<float>(cv::sum(imageGray)[0]);

}


bool EyeAnalyser::LeftRight(float leftValue,float rightValue){

    cout<<"left Value "<<leftValue<<" rightValue "<<rightValue<<endl;
    return false;
}

bool EyeAnalyser::UpDown(float upValue, float downValue){

    cout<<"upValue "<<upValue<<" downValue "<<downValue<<endl;
    return false;
}

short EyeAnalyser::getDistance(const Point &calibration,const deque<Point> &Eye){

    int ACK=0;
    Point Average = averagePoint(Eye);
    cout<<"Average x "<<Average.x<<" Average y"<<Average.y<<endl;
    cout<<"calibration x "<<calibration.x<<" calibration y "<<calibration.y<<endl;
    float distance = static_cast<float>(norm(Average-calibration));
    float angle= ((static_cast<float>(atan2(Average.y - calibration.y, Average.x - calibration.x)))*180)/(static_cast<float>(3.1416));
    cout<<"Distance : "<<distance<<" angle "<<angle<<endl;
    if(distance>sensibility){// not in center
        if((angle >= 135) || (angle <  -135)){ACK=2;} // rigth
        else if((angle >= -135) & (angle <  -45)){ACK=3;}// Up
        else if((angle >= -45) & (angle <  45)){ACK=4;} //left
        else if((angle >= 45) & (angle <  135)){ACK=5;} //down
    }
    else{//center
        ACK=1;
    }
    return ACK;

}
