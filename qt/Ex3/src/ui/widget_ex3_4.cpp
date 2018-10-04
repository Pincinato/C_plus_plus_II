#include "widget_ex3_4.h"
#include "ui_widget_ex3_4.h"
#include <iostream>

widget_ex3_4::widget_ex3_4(QWidget *parent) : QWidget(parent),ui(new Ui::widget_ex3_4)
{
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL (clicked()), this, SLOT (handleButton()));

}

widget_ex3_4::~widget_ex3_4()
{
    delete ui;
}

void widget_ex3_4::handleButton(void){

    std::ifstream in("ekg.txt");
    if (!in) std::cout << " WARNING : File not found !" << std::endl ;
       else{
        plotData(in);
    }
}



void widget_ex3_4::plotData(std::ifstream &in){

    std::vector<double> data;
    copy(std::istream_iterator<int>(in),std::istream_iterator<int>(),back_inserter(data)); //postion, value
    in.close();
    std::vector<std::pair<double,double>> peaks= find_peaks(data);
    std::vector<double> data_x(data.size());
    std::iota(data_x.begin(), data_x.end(), 0);
    presetWindow(ui->widget,"Ex3-p4","Time[s]","Signal[au]");
    ui->widget->graph(0)->setData(QVector<double>::fromStdVector(data_x),QVector<double>::fromStdVector(data));
    ui->widget->rescaleAxes ();
    ui->widget->replot ();

}


std::vector<std::pair<double,double>>widget_ex3_4::find_peaks(const std::vector<double> &data){

    const int threshold = 1140;
    double count=1;
    std::vector<std::pair<double,double>> peaks; //position,value
    for (const auto &it: data){
        if(it >threshold){
            peaks.push_back(std::make_pair(count,it));
        }
        count++;
    }
    return peaks;
}

void widget_ex3_4::presetWindow(QcustomPlot * widget,QString Title, QString X_label,QString Y_label){

    widget->setWindowTitle(Title);
    widget->setInteraction(QCP::iRangeDrag, true);
    widget->setInteraction(QCP::iRangeZoom, true);
    connect (widget, SIGNAL(mouseDoubleClick(QMouseEvent *)),widget, SLOT(rescaleAxes()));
    // Add Graph and s e t some p r o p e r t i e s

    widget->addGraph();
    widget->xAxis->setLabel(X_label);
    widget->yAxis->setLabel(Y_label);
    widget->xAxis->grid()->setSubGridVisible(true);
}
