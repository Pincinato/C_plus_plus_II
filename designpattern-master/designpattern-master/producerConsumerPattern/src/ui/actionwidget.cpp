#include "actionwidget.h"
#include "ui_actionwidget.h"

ActionWidget::ActionWidget(QWidget *parent,const string &CamOp,const Point &calibrationLeft,const Point &calibrationRight) :
    QWidget(parent),
    ui(new Ui::ActionWidget),
    calibrationEyeLeft(calibrationLeft),
    calibrationEyeRight(calibrationRight),
    CamOption(CamOp)
{
    ui->setupUi(this);
    m_lastData.reset();
    m_appCtrl.reset( new Control(this) );
     connect(ui->BackButton,SIGNAL(clicked()),this,SLOT(buttonBack()));
    //setting button layout;
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

void ActionWidget::buttonBack(){

    emit back();
}

