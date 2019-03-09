#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calibrationwidget.h"
#include "widget.h"
#include <qmessagebox.h>
#include <QCameraInfo>
#include <QCamera>
#include <QWidget>
#include "icalibrationwidget.h"
#include "actionwidget.h"

class Widget;

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow),
    m_CamOption("WebCam")
{
    ui->setupUi(this);
    connect(ui->Calibration,SIGNAL(clicked()),this,SLOT(calibration()));
    connect(ui->Start,SIGNAL(clicked()),this,SLOT(start()));
    connect(ui->EyeDetection,SIGNAL(clicked()),this,SLOT(eyeDetectionView()));
    m_Iscalibrated=false;
    m_calibrationEyeRight = cv::Point(0,0);
    m_calibrationEyeLeft = cv::Point(0,0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myShow(){
    this->showFullScreen();
    QPixmap newImage("images/background.png");
    newImage = newImage.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, newImage);
    this->setPalette(palette);
    ui->Exit->move(this->size().width() - 3*ui->Exit->size().width(),this->size().height() - 3*ui->Exit->size().height());
    ui->Calibration->move(this->size().width() - this->size().width()/2 - ui->Calibration->size().width()/2,this->size().height() - this->size().height()/2 - ui->Calibration->size().height()/2);
    ui->Start->move(ui->Calibration->x(),ui->Calibration->y()- 3*ui->Start->size().height());
    ui->EyeDetection->move(ui->Calibration->x() ,ui->Calibration->y() +  3*ui->EyeDetection->size().height());
}


void  MainWindow::initCalibration(){
    m_Iscalibrated=false;
    m_calibrator.reset(new CalibrationWidget(nullptr,this,m_CamOption));
    connect(m_calibrator.get(),SIGNAL(back()),this,SLOT(backCalibrationView()));
}

void  MainWindow::initEyeDetection(){
    eyeDetectionWidget.reset(new Widget);
    connect(eyeDetectionWidget.get(),SIGNAL(back()),this,SLOT(backEyeDetectionView()));
}

void  MainWindow::initActionWidget(){

    m_actionWigdet.reset(new ActionWidget(nullptr,m_CamOption,m_calibrationEyeLeft,m_calibrationEyeRight));
    connect(m_actionWigdet.get(),SIGNAL(back()),this,SLOT(backActionView()));

}

void MainWindow::start(){

    if(m_Iscalibrated==false){
        QMessageBox msgBox;
        msgBox.setText("A calibration is needed.");
        msgBox.exec();
    }
    else{
         int numberOfCamera=QCameraInfo::availableCameras().count();
        if(numberOfCamera>=2){
            initActionWidget();
            m_actionWigdet->myShow();
        }
        else if(numberOfCamera==1 && (m_CamOption== "WebCam")){
            initActionWidget();
            m_actionWigdet->myShow();
        }
        else{
            QMessageBox msgBox;
            msgBox.setText("Selected Camera was disconnected");
            msgBox.exec();
        }
   }
}

void MainWindow::calibration(){
    int numberOfCamera=QCameraInfo::availableCameras().count();
    if(numberOfCamera>=2){
        initCalibration();
        m_calibrator->myShow();
    }
    else if(numberOfCamera==1 && (m_CamOption== "WebCam")){
        initCalibration();
        m_calibrator->myShow();
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Selected Camera was disconnected");
        msgBox.exec();
    }
}

void MainWindow::eyeDetectionView(){
    int numberOfCamera=QCameraInfo::availableCameras().count();
    if(numberOfCamera>=1){
    initEyeDetection();
    eyeDetectionWidget->myShow();
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Selected Camera was disconnected");
        msgBox.exec();
    }
}

void MainWindow::backEyeDetectionView(){


    if(eyeDetectionWidget->getCamOption()!=m_CamOption){m_Iscalibrated=false;}
    m_CamOption.clear();
    m_CamOption.append(eyeDetectionWidget->getCamOption());
    eyeDetectionWidget->close();    
    eyeDetectionWidget.reset();
}

void MainWindow::backCalibrationView(){

    m_calibrator->close();
    m_calibrator.reset();

}

void MainWindow::backActionView(){

    m_actionWigdet->close();
    m_actionWigdet.reset();
}

void MainWindow::setCalibrationPoint(const cv::Point &eyeLeft,const cv::Point &eyeRight){
    m_calibrationEyeLeft=eyeLeft;
    m_calibrationEyeRight=eyeRight;
    m_Iscalibrated=true;
}


