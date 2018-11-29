#include "mainwindow.h"
#include "ui_mainwindow.h"

class Widget;

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    eyeDetectionWidget.reset(new Widget);
    calibrator.reset(new CalibrationWidget);
    m_actionWigdet.reset(new ActionWidget);
    //eyeDetectionWidget.reset(new Widget);
    connect(ui->Calibration,SIGNAL(clicked()),this,SLOT(calibration()));
    connect(ui->Start,SIGNAL(clicked()),this,SLOT(start()));
    connect(ui->EyeDetection,SIGNAL(clicked()),this,SLOT(eyeDetectionView()));
    connect(eyeDetectionWidget.get(),SIGNAL(back()),this,SLOT(backEyeDetectionView()));
    connect(calibrator.get(),SIGNAL(back()),this,SLOT(backCalibrationView()));
    connect(m_actionWigdet.get(),SIGNAL(back()),this,SLOT(backActionView()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start(){

    m_actionWigdet->setCamOption(CamOption);
    m_actionWigdet->myShow();
    this->hide();
}

void MainWindow::calibration(){

    calibrator->setCamoption(CamOption);
    calibrator->myShow();
    this->hide();
}

void MainWindow::eyeDetectionView(){

    eyeDetectionWidget->show();
    this->hide();
}

void MainWindow::backEyeDetectionView(){

    this->show();
    eyeDetectionWidget->close();
    CamOption.clear();
    CamOption.append(eyeDetectionWidget->getCamOption());
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
}


