#include "actionwidget.h"
#include "ui_actionwidget.h"
#include "control.h"
#include <QTimer>

ActionWidget::ActionWidget(QWidget *parent,const string &CamOp,const Point &calibrationLeft,const Point &calibrationRight) :
    QWidget(parent),
    ui(new Ui::ActionWidget),
    m_calibrationEyeLeft(calibrationLeft),
    m_calibrationEyeRight(calibrationRight),
    m_UpdateRateMS(10)
{
    ui->setupUi(this);
    m_lastData.reset();
    m_appCtrl.reset( new Control(this) );
    m_appCtrl->setCamera(CamOp);
    connect(ui->BackButton,SIGNAL(clicked()),this,SLOT(buttonBack()));
    m_UpdateTimer.reset(new QTimer(this));
    connect( m_UpdateTimer.get(), SIGNAL(timeout()), this, SLOT(Update()) );


}

ActionWidget::~ActionWidget()
{
    delete ui;
}

void ActionWidget::myShow(){


    QPixmap ButtonImage("images/back_button.png");
    QIcon ButtonIcon(ButtonImage);
    ui->BackButton->setIcon(ButtonIcon);
    ui->BackButton->setIconSize(ButtonImage.rect().size());
    ui->BackButton->setFixedSize(ButtonImage.rect().size());
    this->showFullScreen();
    ui->BackButton->move(this->size().width() - ui->BackButton->size().width(),this->size().height() - ui->BackButton->size().height());
    QPixmap bkgnd1("images/center.png");
    setBackground(bkgnd1);
    m_UpdateTimer->start(m_UpdateRateMS);
    m_appCtrl->startPlaying();    
    ui->SensibilitySlider->setMaximum(50);
    ui->SensibilitySlider->setMinimum(1);
    ui->SensibilitySlider->setValue(10);
}

void ActionWidget::displayMsg(const std::string &tag, const std::string &msg) {
    std::cout << " Info: " << tag << " : " <<  msg << std::endl;
}

void ActionWidget::setData(DataBufferPtr data){
    m_lastData = data;
}
void ActionWidget::setPoint(const cv::Point &eyeLeft,const cv::Point &eyeRight){
    cv::Point a,b;
    a=eyeLeft;
    b=eyeRight;
}

void ActionWidget::Update(){

    if( m_lastData )
    {
        if(m_appCtrl->getEyes(m_lastData)){
            int ret = m_appCtrl->getDirection(m_calibrationEyeLeft,m_calibrationEyeRight);
            if(ret==1){
                QPixmap bkgnd1("images/center.png");
                setBackground(bkgnd1);
            }
            else if(ret==2){
                QPixmap bkgnd1("images/right.png");
                setBackground(bkgnd1);
            }
            else if(ret==3){
                QPixmap bkgnd1("images/up.png");
                setBackground(bkgnd1);
            }
            else if(ret==4){
                QPixmap bkgnd1("images/left.png");
                setBackground(bkgnd1);
            }
            else if(ret==5){
                QPixmap bkgnd1("images/down.png");
                setBackground(bkgnd1);
            }
        m_appCtrl->clearVectors();
        }
    }
    m_appCtrl->setSensibility(ui->SensibilitySlider->value());
}

void ActionWidget::setBackground(QPixmap newImage){

    newImage = newImage.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, newImage);
    this->setPalette(palette);

}

void ActionWidget::buttonBack(){
    m_appCtrl->stopPlaying();
    emit back();
}

