#include "widget.h"
#include "ui_widget.h"
#include <functional>
#include <algorithm>

Widget::Widget(QWidget *parent) :QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    std::function<double(double)> x_square=[](double x){return  x*x;};
    std::function<double(double)> inverse_x=[](double x){return  1/x;};
    plotData(x_square,inverse_x);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::plotData(const std::function<double(double)> &function1,const std::function<double(double)> &function2){

    ui->qcpwidget->setWindowTitle("Ex 3 part 2");
    ui->qcpwidget->setInteraction(QCP::iRangeDrag, true);
    ui->qcpwidget->setInteraction(QCP::iRangeZoom, true);
    connect (ui->qcpwidget, SIGNAL(mouseDoubleClick(QMouseEvent *)), ui->qcpwidget, SLOT(rescaleAxes()));
    // Add Graph and s e t some p r o p e r t i e s
    ui->qcpwidget->addGraph();
    ui->qcpwidget->xAxis->setLabel("X");
    ui->qcpwidget->yAxis->setLabel("Y");
    ui->qcpwidget->xAxis->grid()->setSubGridVisible(true);
    //Cr e a t e data : f ( x ) = x^2
    std :: vector < double > X (101) ;
    std :: iota (X. begin () ,X. end () , -50);
    std :: vector < double > Y (101) ;
    std :: vector < double > Y_normalize (101) ;
    //First function
    std :: transform (X.begin() ,X.end(),Y.begin() ,[function1](double x){return (function1(x));});
    auto max= std::max_element(Y.cbegin(),Y.cend());
    std :: transform (Y.begin(),Y.end(),Y_normalize.begin() ,[max](double x){return (x/(*max));}); //Normalized
    // Plot data
    ui->qcpwidget->graph(0)->setData( QVector < double >:: fromStdVector (X),QVector < double >:: fromStdVector(Y_normalize));
    ui->qcpwidget->graph(0)->setName("x*x");
    ui->qcpwidget->rescaleAxes ();
    ui->qcpwidget->replot ();
    //Second Graph
    ui->qcpwidget->addGraph();
    // Second function
    std :: transform (X.begin() ,X.end(),Y.begin() ,[function2](double x){return (function2(x));});
    //Plot setting
    ui->qcpwidget->graph(1)->setPen(QPen(Qt::red));
    ui->qcpwidget->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->qcpwidget->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 6));
    ui->qcpwidget->graph(1)->setData( QVector < double >:: fromStdVector (X), QVector < double >:: fromStdVector(Y));
    ui->qcpwidget->graph(1)->setName("1/x");
    ui->qcpwidget->replot();
    // Legend
    ui->qcpwidget->legend->setVisible(true);
    QFont legendFont = font();  // start out with MainWindow's font..
    legendFont.setPointSize(9); // and make a bit smaller for legend
    ui->qcpwidget->legend->setFont(legendFont);
    ui->qcpwidget->legend->setBrush(QBrush(QColor(255,255,255,255)));
    ui->qcpwidget->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignLeft); //alignement

}
