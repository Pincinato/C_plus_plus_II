#include "calibrationwidget.h"
#include "ui_calibrationwidget.h"
#include <QKeyEvent>
#include "control.h"

CalibrationWidget::CalibrationWidget(QWidget *parent,ICalibrationWidget *owner, const string &CamOp) :
    QWidget(parent),
    ui(new Ui::CalibrationWidget),
    m_owner(owner)
{
    ui->setupUi(this);
    m_lastData.reset();
    m_appCtrl.reset( new Control(this) );
    m_appCtrl->setCamera(CamOp);
    enableButtons(false);
    //connect bottuns
    connect(ui->RefuseButton,SIGNAL(clicked()),this,SLOT(Refuse()));
    connect(ui->AcceptButton,SIGNAL(clicked()),this,SLOT(Accept()));
    this->showFullScreen();
}

CalibrationWidget::~CalibrationWidget()
{
    delete ui;
}

void CalibrationWidget::displayMsg(const std::string &tag, const std::string &msg)
{
    std::cout << " Info: " << tag << " : " <<  msg << std::endl;
}

void CalibrationWidget::setData(DataBufferPtr data)
{
    m_lastData = data;
}

void CalibrationWidget::myShow(){

    this->showFullScreen();
    QPixmap bkgnd("images/calibration.png");
    setBackground(bkgnd);
    m_appCtrl->startPlaying();
}

void CalibrationWidget::keyPressEvent(QKeyEvent *ev){


    if(ev->key()==Qt::Key_Space){
        if(m_lastData){
            if(m_appCtrl->getEyes(m_lastData)){
                m_appCtrl->stopPlaying();
                m_appCtrl->setEyesInFrame(m_lastData);
                m_appCtrl->setEyesCenter(m_lastData);
                QPixmap newImage;
                if(newImage.convertFromImage(m_lastData->m_image)){
                    setBackground(newImage);
                    enableButtons(true);
                }
            }
        }
    }
    if(ev->key()==Qt::Key_Escape){
        m_appCtrl->stopPlaying();
        emit back();
    }
}

void CalibrationWidget::setBackground(QPixmap newImage){

    newImage = newImage.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, newImage);
    this->setPalette(palette);

}

void CalibrationWidget::enableButtons(bool op){


    ui->AcceptButton->setEnabled(op);
    ui->RefuseButton->setEnabled(op);
    if (op){
        ui->AcceptButton->show();
        ui->RefuseButton->show();
    }
    else{
        ui->AcceptButton->hide();
        ui->RefuseButton->hide();
    }
}

void CalibrationWidget::Accept(){

    emit back();

}

void CalibrationWidget::Refuse(){

    QPixmap bkgnd("images/calibration.png");
    setBackground(bkgnd);
    enableButtons(false);
    m_appCtrl->startPlaying();
}

void CalibrationWidget::setPoint(const cv::Point &eyeLeft,const cv::Point &eyeRight){
    m_owner->setCalibrationPoint(eyeLeft,eyeRight);
}

