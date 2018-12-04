#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmessagebox.h>

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
    m_calibrationEyeRight = Point(0,0);
    m_calibrationEyeLeft = Point(0,0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myShow(){

    this->showFullScreen();
}


void  MainWindow::initCalibration(){
    m_Iscalibrated=false;
    calibrator.reset(new CalibrationWidget(nullptr,this,m_CamOption));
    connect(calibrator.get(),SIGNAL(back()),this,SLOT(backCalibrationView()));
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
        initActionWidget();
        m_actionWigdet->myShow();
        this->hide();
   }
}

void MainWindow::calibration(){

    initCalibration();
    calibrator->myShow();
    this->hide();
}

void MainWindow::eyeDetectionView(){
    initEyeDetection();
    eyeDetectionWidget->show();
    this->hide();
}

void MainWindow::backEyeDetectionView(){

    this->showFullScreen();
    if(eyeDetectionWidget->getCamOption()!=m_CamOption){m_Iscalibrated=false;}
    m_CamOption.clear();
    m_CamOption.append(eyeDetectionWidget->getCamOption());
    eyeDetectionWidget->close();    
    eyeDetectionWidget.reset();
}

void MainWindow::backCalibrationView(){
    this->showFullScreen();
    calibrator->close();
    calibrator.reset();

}

void MainWindow::backActionView(){
    this->showFullScreen();
    m_actionWigdet->close();
    m_actionWigdet.reset();
}

void MainWindow::setCalibrationPoint(const cv::Point &eyeLeft,const cv::Point &eyeRight){
    m_calibrationEyeLeft=eyeLeft;
    m_calibrationEyeRight=eyeRight;
    m_Iscalibrated=true;
}


