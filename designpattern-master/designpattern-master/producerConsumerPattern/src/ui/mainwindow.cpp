#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmessagebox.h>

class Widget;

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow),
    CamOption("WebCam")
{
    ui->setupUi(this);
    connect(ui->Calibration,SIGNAL(clicked()),this,SLOT(calibration()));
    connect(ui->Start,SIGNAL(clicked()),this,SLOT(start()));
    connect(ui->EyeDetection,SIGNAL(clicked()),this,SLOT(eyeDetectionView()));
    Iscalibrated=false;
    calibrationEyeRight = Point(0,0);
    calibrationEyeLeft = Point(0,0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void  MainWindow::initCalibration(){
    Iscalibrated=false;
    calibrator.reset(new CalibrationWidget(nullptr,this,CamOption));
    connect(calibrator.get(),SIGNAL(back()),this,SLOT(backCalibrationView()));
}

void  MainWindow::initEyeDetection(){
    eyeDetectionWidget.reset(new Widget);
    connect(eyeDetectionWidget.get(),SIGNAL(back()),this,SLOT(backEyeDetectionView()));
}

void  MainWindow::initActionWidget(){

    m_actionWigdet.reset(new ActionWidget(nullptr,CamOption,calibrationEyeLeft,calibrationEyeRight));
    connect(m_actionWigdet.get(),SIGNAL(back()),this,SLOT(backActionView()));

}

void MainWindow::start(){
    if(Iscalibrated==false){
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

    this->show();
    if(eyeDetectionWidget->getCamOption()!=CamOption){Iscalibrated=false;}
    CamOption.clear();
    CamOption.append(eyeDetectionWidget->getCamOption());
    eyeDetectionWidget->close();
     calibrator.reset();
}

void MainWindow::backCalibrationView(){
    this->show();
    calibrator->close();
}

void MainWindow::backActionView(){
    this->show();
    m_actionWigdet->close();
}

void MainWindow::setCalibrationPoint(const cv::Point &eyeLeft,const cv::Point &eyeRight){
    calibrationEyeLeft=eyeLeft;
    calibrationEyeRight=eyeRight;
    Iscalibrated=true;
}


