#include "mainwindow.h"
#include "ui_mainwindow.h"

class Widget;

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    eyeDetectionWidget = new Widget;
    //eyeDetectionWidget.reset(new Widget);
    connect(ui->Calibration,SIGNAL(clicked()),this,SLOT(calibration()));
    connect(ui->Start,SIGNAL(clicked()),this,SLOT(start()));
    connect(ui->EyeDetection,SIGNAL(clicked()),this,SLOT(eyeDetectionView()));
    connect(eyeDetectionWidget,SIGNAL(back()),this,SLOT(backEyeDetectionView()));
}

MainWindow::~MainWindow()
{
    delete eyeDetectionWidget;
    delete ui;
}

void MainWindow::start(){

}

void MainWindow::calibration(){

}

void MainWindow::eyeDetectionView(){

    eyeDetectionWidget->show();
    this->hide();
}

void MainWindow::backEyeDetectionView(){

    this->show();
    eyeDetectionWidget->close();
}
