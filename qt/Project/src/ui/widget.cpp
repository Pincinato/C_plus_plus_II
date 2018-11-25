#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(new QGraphicsScene(this));
    ui->graphicsView->scene()->addItem(&pixmap);
    connect(ui->Start,SIGNAL (clicked()), this, SLOT (start()));
    connect(ui->Stop,SIGNAL (clicked()), this, SLOT (stop()));
    detector.reset(new Eye_detector(this));
    m_UpdateTimer.reset( new QTimer(this));
    //connect( m_UpdateTimer.get(), SIGNAL(timeout()), this, SLOT(updateWidget()) );
    m_UpdateTimer->start(20);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::start(){
     detector->start();
}

void Widget::stop(){
    detector->stop();
}


void Widget::setData(Mat &frame){
   this->frame=frame;
   // updateWidget();
    imshow( "window_name", frame );
    qApp->processEvents();
}
void Widget::setStatus(string cameraStatus){

}

void Widget::updateWidget(){
    if(!frame.empty()){
        QImage qimg(frame.data,frame.cols,frame.rows,frame.step,QImage::Format_RGB888);
        pixmap.setPixmap( QPixmap::fromImage(qimg.rgbSwapped()) );
        ui->graphicsView->fitInView(&pixmap, Qt::KeepAspectRatio);
        qApp->processEvents();
    }
}
