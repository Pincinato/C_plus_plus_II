#include "actionwidget.h"
#include "ui_actionwidget.h"

ActionWidget::ActionWidget(QWidget *parent,const string &CamOp,const Point &calibrationLeft,const Point &calibrationRight) :
    QWidget(parent),
    ui(new Ui::ActionWidget),
    calibrationEyeLeft(calibrationLeft),
    calibrationEyeRight(calibrationRight),
    CamOption(CamOp),
    m_UpdateRateMS(10)
{
    ui->setupUi(this);
    m_lastData.reset();
    m_appCtrl.reset( new Control(this) );
    connect(ui->BackButton,SIGNAL(clicked()),this,SLOT(buttonBack()));
    //
    m_UpdateTimer.reset(new QTimer(this));
    connect( m_UpdateTimer.get(), SIGNAL(timeout()), this, SLOT(Update()) );
    m_UpdateTimer->start(m_UpdateRateMS);


}

ActionWidget::~ActionWidget()
{
    delete ui;
}

void ActionWidget::myShow(){


    QPixmap ButtonImage("back_button.png");
    QIcon ButtonIcon(ButtonImage);
    ui->BackButton->setIcon(ButtonIcon);
    ui->BackButton->setIconSize(ButtonImage.rect().size());
    ui->BackButton->setFixedSize(ButtonImage.rect().size());
    this->showFullScreen();
    QPixmap bkgnd1("center.png");
    setBackground(bkgnd1);
    m_appCtrl->startPlaying();
}

void ActionWidget::setCamOption(const string &Cam){
    CamOption.clear();
    CamOption.append(Cam);
}

void ActionWidget::displayMsg(const std::string &tag, const std::string &msg) {
    std::cout << " Info: " << tag << " : " <<  msg << std::endl;
}

void ActionWidget::setData(DataBufferPtr data){
    m_lastData = data;
}
void ActionWidget::setPoint(const cv::Point &eyeLeft,const cv::Point &eyeRight){
    std::cout << " Point x: " << eyeLeft.x << " y:" <<  eyeLeft.y << std::endl;
    std::cout << " Point x: " << eyeRight.x << " y:" <<  eyeRight.y << std::endl;
}

void ActionWidget::Update(){

     std::cout << " Update Action"<<std::endl;
    if( m_lastData )
    {
        if(m_appCtrl->getEyes(m_lastData)){
            int ret = (m_appCtrl->getDirection(m_lastData,calibrationEyeLeft,calibrationEyeRight));
            if(ret==1){
                QPixmap bkgnd1("center.png");
                setBackground(bkgnd1);
            }
            else if(ret==2){
                QPixmap bkgnd1("right.png");
                setBackground(bkgnd1);
            }
            else if(ret==3){
                QPixmap bkgnd1("up.png");
                setBackground(bkgnd1);
            }
            else if(ret==4){
                QPixmap bkgnd1("left.png");
                setBackground(bkgnd1);
            }
            else if(ret==5){
                QPixmap bkgnd1("down.png");
                setBackground(bkgnd1);
            }
        m_appCtrl->clearVectors();
        }
    }
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

