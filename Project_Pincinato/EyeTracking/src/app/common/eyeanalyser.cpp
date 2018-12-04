#include "eyeAnalyser.h"

#include <QWidget>
#include "icontrol.h"
#include "control.h"
#include <string>
#include <algorithm>
using namespace std;

EyeAnalyser::EyeAnalyser()
{
    sensibility=10;
    m_valueX.clear();
    m_valueY.clear();
}

short EyeAnalyser::getDirection(const Point &calibrationLeft,const Point &calibrationRight,const deque<Point> &leftEye,const deque<Point> &rightEye){

    getDistance(calibrationRight,rightEye);
     return getDistance(calibrationLeft,leftEye);

}

Point EyeAnalyser::medianPoint(const deque<Point> &input){

    Point Median(0,0);
    vector<Point> vec(input.begin(),input.end());
    sort(vec.begin(),vec.end(),[](Point firstElem,Point secondElem){
         return firstElem.x > secondElem.x;
    });
    Median.x=vec[vec.size()/2].x;
    sort(vec.begin(),vec.end(),[](Point firstElem,Point secondElem){
         return firstElem.y > secondElem.y;
    });
    Median.y=vec[vec.size()/2].y;
    return Median;
}


short EyeAnalyser::getDistance(const Point &calibration,const deque<Point> &Eye){

    short ACK=0;
    Point Average = medianPoint(Eye);
    cout<<"Average x "<<Average.x<<" Average y"<<Average.y<<endl;
    cout<<"calibration x "<<calibration.x<<" calibration y "<<calibration.y<<endl;
    float distance = static_cast<float>(norm(Average-calibration));
    float angle= ((static_cast<float>(atan2(Average.y - calibration.y, Average.x - calibration.x)))*180)/(static_cast<float>(3.1416));
    cout<<"Distance : "<<distance<<" angle "<<angle<<endl;
    if((distance>sensibility) & (distance <100)){// not in center
        if((angle >= 135) || (angle <  -135)){ACK=2;} // rigth
        else if((angle >= -135) & (angle <  -45)){ACK=3;}// Up
        else if((angle >= -45) & (angle <  45)){ACK=4;} //left
        else if((angle >= 45) & (angle <  135)){ACK=5;} //down
    }
    else if (distance<sensibility){//center
        ACK=1;
    }
    return ACK;

}

void EyeAnalyser::setSensibility(int newValue){
    sensibility=newValue;
}