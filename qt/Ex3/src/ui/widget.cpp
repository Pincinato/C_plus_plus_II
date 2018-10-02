#include "widget.h"
#include "ui_widget.h"
#include <functional>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    std::function<double(double)> x_square=[](double x){return  x*x;};
    std::function<double(double)> inverse_x=[](double x){return  1/x;};
    plotData(ui->qcpwidget,x_square);//, {return x*x;});
    plotData(ui->qcp_1_x_widget,inverse_x);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::plotData(QcustomPlot *widget,const std::function<double(double)> &function){

    widget->setInteraction( QCP :: iRangeDrag , true );
    widget->setInteraction( QCP :: iRangeZoom , true );
    connect (widget , SIGNAL ( mouseDoubleClick ( QMouseEvent *)),
    widget , SLOT ( rescaleAxes ()) );
    // Add Graph and s e t some p r o p e r t i e s
    widget->addGraph();
    widget->xAxis->setLabel("X");
    widget->yAxis->setLabel("Y");
    widget->xAxis->grid () -> setSubGridVisible ( true );
    //Cr e a t e data : f ( x ) = x^2
    std :: vector < double > X (101) ;
    std :: iota (X. begin () ,X. end () , -50);
    std :: vector < double > Y (101) ;
    std :: transform (X.begin() ,X.end(),Y.begin() ,[function](double x){return (function(x));});
    // Pl o t data
    widget->graph(0)->setData( QVector < double >:: fromStdVector (X),
    QVector < double >:: fromStdVector(Y));
    //
    widget->rescaleAxes ();
    widget->replot ();
}
