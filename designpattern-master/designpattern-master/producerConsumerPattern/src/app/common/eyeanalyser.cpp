#include "eyeanalyser.h"

#include <QWidget>
#include "icontrol.h"
#include "control.h"
#include <string>
#include <algorithm>
using namespace std;

EyeAnalyser::EyeAnalyser()
{
    sensibility=10;
    valueX.clear();
    valueY.clear();
}

std::vector<cv::Point> centers;

cv::Vec3f getEyeball(cv::Mat &eye, std::vector<cv::Vec3f> &circles)
{
  std::vector<int> sums(circles.size(), 0);
  for (int y = 0; y < eye.rows; y++)
  {
      uchar *ptr = eye.ptr<uchar>(y);
      for (int x = 0; x < eye.cols; x++)
      {
          int value = static_cast<int>(*ptr);
          for (int i = 0; i < circles.size(); i++)
          {
              cv::Point center((int)std::round(circles[i][0]), (int)std::round(circles[i][1]));
              int radius = (int)std::round(circles[i][2]);
              if (std::pow(x - center.x, 2) + std::pow(y - center.y, 2) < std::pow(radius, 2))
              {
                  sums[i] += value;
              }
          }
          ++ptr;
      }
  }
  int smallestSum = 9999999;
  int smallestSumIndex = -1;
  for (int i = 0; i < circles.size(); i++)
  {
      if (sums[i] < smallestSum)
      {
          smallestSum = sums[i];
          smallestSumIndex = i;
      }
  }
  return circles[smallestSumIndex];
}

cv::Point stabilize(std::vector<cv::Point> &points, int windowSize)
{
  float sumX = 0;
  float sumY = 0;
  int count = 0;
  for (int i = std::max(0, (int)(points.size() - windowSize)); i < points.size(); i++)
  {
      sumX += points[i].x;
      sumY += points[i].y;
      ++count;
  }
  if (count > 0)
  {
      sumX /= count;
      sumY /= count;
  }
  return cv::Point(sumX, sumY);
}


short EyeAnalyser::getEyePosition(const Mat &frame,const deque<Point> &leftEye,const deque<Point> &rightEye,const Mat &Eyetemplate){
    const int MINIMALAREA=50;
    short ACK=0;
    Point leftAverage = averagePoint(leftEye);
    Point rightAverage= averagePoint(rightEye);
    int width = (static_cast<int>(static_cast<float>((rightAverage.x-leftAverage.x)*0.6)));//0.8// need to check!!!
    int height= static_cast<int>(width*0.5);//0.5//0.3//radio  ~0.4
    /// Create the result matrix
    //Setting mask of whole left eye



    if( (leftAverage.x>width/2) && (leftAverage.y>height/2)){
        Rect Left(leftAverage.x-width/2,leftAverage.y-height/2,width,height);
        if (Left.area()>MINIMALAREA) {
            Mat frameCopy;
            frame.copyTo(frameCopy);
            Mat image=frameCopy(Left);
            //cv::equalizeHist(image, image);
            int result_cols =  image.cols - Eyetemplate.cols + 1;
            int result_rows = image.rows - Eyetemplate.rows + 1;
            Mat result ( result_rows, result_cols, CV_32FC1 );
            Point matchLoc(0,0);
            matchTemplate( image, Eyetemplate, result, CV_TM_CCORR_NORMED);
            double minVal; double maxVal; Point minLoc; Point maxLoc;
            minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
            matchLoc = maxLoc;
            cout <<" center leftAverage x "<<leftAverage.x<<" center leftAverage y "<<leftAverage.y<<endl;
            cout <<" mathLoc x "<<matchLoc.x<<" matchLoc y "<<matchLoc.y<<" maxVal"<<maxVal<<endl;
            valueX.push_front(matchLoc.x);
            valueY.push_front(matchLoc.y);
            if(valueX.size()>5){valueX.pop_back();}
            if(valueY.size()>5){valueY.pop_front();}
            int AverageX = (accumulate(valueX.begin(), valueX.end(), 0)) / static_cast<int>(valueX.size());
            int AverageY = (accumulate(valueY.begin(), valueY.end(), 0)) / static_cast<int>(valueY.size());
            if ((AverageX< 7)){ACK=2;}//right
            else if(AverageY<5){ACK=3;}//up
            else if(AverageX>=33){ ACK=4;}//left
            else if ((AverageX< 24) &(AverageX>=15)){ACK=1;}//center

            rectangle( image, matchLoc, Point( AverageX + Eyetemplate.cols ,AverageY + Eyetemplate.rows ), Scalar::all(0), 2, 8, 0 );
            rectangle( result, matchLoc, Point( AverageX + Eyetemplate.cols , AverageY + Eyetemplate.rows ), Scalar::all(0), 2, 8, 0 );
            //imshow( "image_window", frameCopy );
            //imshow( "result_window", result );
            imshow("template",Eyetemplate);
            imshow("image",image);
            }
        }


    /*
    if( (leftAverage.x>width/2) && (leftAverage.y>height/2)){
        Rect Left(leftAverage.x-width/2,leftAverage.y-height/2,width,height);
        if (Left.area()>MINIMALAREA) {
              Mat frameCopy;
              frame.copyTo(frameCopy);
              Mat cropeed=frameCopy(Left);
              Mat eye;
              cv::cvtColor(cropeed, eye, CV_BGR2GRAY);
              cv::equalizeHist(eye, eye);
              std::vector<cv::Vec3f> circles;
              cv::HoughCircles(eye, circles, CV_HOUGH_GRADIENT, 1, eye.cols / 8, 250, 15, eye.rows / 8, eye.rows / 3);
              if (circles.size() > 0)
                {
                    cv::Vec3f eyeball = getEyeball(eye, circles);
                    cv::Point center(eyeball[0], eyeball[1]);
                    centers.push_back(center);
                    center = stabilize(centers, 5);
                    cv::circle(eye,center,2, cv::Scalar(0, 0, 255)[3], 2);
                    //cv::circle(eye, center, radius, cv::Scalar(255, 255, 255), 2);
                    imshow("Image",eye);
                }

        }
    }
    */
    return ACK;
    //return 0;

}


short EyeAnalyser::getDirection(const Mat &frame,const Point &calibrationLeft,const Point &calibrationRight,const deque<Point> &leftEye,const deque<Point> &rightEye,const Mat &Eyetemplate){

     //Mat gray_frame;
     //cvtColor(frame, gray_frame, CV_BGR2GRAY);
     //Mat gray_template;
     //cvtColor(Eyetemplate, gray_template, CV_BGR2GRAY);
     //return getEyePosition(frame,leftEye,rightEye,Eyetemplate);

    //return 0;
    //return getEyePosition(frame,leftEye,rightEye,Eyetemplate);
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

    short ACK=0;
    Point Average = averagePoint(Eye);
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
