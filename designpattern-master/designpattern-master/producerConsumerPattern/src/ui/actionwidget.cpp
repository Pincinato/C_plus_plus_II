#include "actionwidget.h"
#include "ui_actionwidget.h"

ActionWidget::ActionWidget(QWidget *parent,const string &CamOp) :
    QWidget(parent),
    ui(new Ui::ActionWidget),
    CamOption(CamOp)
{
    ui->setupUi(this);
    m_lastData.reset();
    m_appCtrl.reset( new Control(this) );
     connect(ui->BackButton,SIGNAL(clicked),this,SLOT(buttonBack()));
    //setting button layout;
}

ActionWidget::~ActionWidget()
{
    delete ui;
}

void ActionWidget::myShow(){


    QPixmap newImage("back_button.png");
    newImage = newImage.scaled(ui->BackButton->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, newImage);
    this->setPalette(palette);
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
void ActionWidget::setPoint(const cv::Point eye_center){
    std::cout << " Point x: " << eye_center.x << " y:" <<  eye_center.y << std::endl;
}

void ActionWidget::buttonBack(){

    emit back();
}

