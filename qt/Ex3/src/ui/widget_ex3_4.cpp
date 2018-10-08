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
    if (!in) {
        std::cout << " WARNING : File not found !" << std::endl ;
        QMessageBox msgBox;
        msgBox.setText("File not found !");
        msgBox.exec();
    }
    else{
        plotData(in);
    }
}



void widget_ex3_4::plotData(std::ifstream &in){

    std::vector<double> data;
    const int sample_freq=360;
    copy(std::istream_iterator<int>(in),std::istream_iterator<int>(),back_inserter(data)); //postion, value
    in.close();
    std::vector<double> data_x(data.size());
    std::vector<double> x(data.size());
    std::iota(data_x.begin(), data_x.end(),0);
    std::transform(data_x.cbegin(),data_x.cend(),x.begin(),[](double x){return (x/sample_freq);});
    presetWindow(ui->widget,"Ex3-p4","Time[s]","Signal[au]");
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(QVector<double>::fromStdVector(x),QVector<double>::fromStdVector(data));
    ui->widget->rescaleAxes();
    ui->widget->replot();
    std::vector<std::pair<double,double>> peaks = find_peaks(data,100,1140); //position, value
    std::vector<double> peaks_y(peaks.size());
    std::transform(peaks.cbegin(),peaks.cend(),peaks_y.begin(),[](std::pair<double,double> x){return x.second;});
    std::vector<double> peaks_x(peaks.size());
    std::transform(peaks.cbegin(),peaks.cend(),peaks_x.begin(),[](std::pair<double,double> x){return (x.first/sample_freq);});
    ui->widget->addGraph();
    ui->widget->graph(1)->setPen(QPen(Qt::red));
    ui->widget->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,7));
    ui->widget->graph(1)->setData(QVector<double>::fromStdVector(peaks_x),QVector<double>::fromStdVector(peaks_y));
    ui->widget->rescaleAxes();
    ui->widget->replot();
    double average= 60*(peaks_x.size())/(*(peaks_x.cend()-1)-*(peaks_x.cbegin()));
    ui->label->setText("Average Heart Rate \n" + QString("%1").arg(average)+" bpm");
}


std::vector<std::pair<double,double>>widget_ex3_4::find_peaks(const std::vector<double> &data,const uint window, const int threshold){

    std::vector<std::pair<double,double>> peaks; //position,value
      for(uint i=1; i < data.size()/window ;i++){
       auto it=std::max_element(data.begin()+(i-1)*window,data.begin()+(i)*window);
       double index = static_cast<double> (std::distance(data.begin(),it));
       if((*it)>threshold){peaks.push_back(std::make_pair(index,(*it)));};
     }

     return peaks;
}

void widget_ex3_4::presetWindow(QcustomPlot * widget,QString Title, QString X_label,QString Y_label){

    widget->setWindowTitle(Title);
    widget->setInteraction(QCP::iRangeDrag, true);
    widget->setInteraction(QCP::iRangeZoom, true);
    connect (widget, SIGNAL(mouseDoubleClick(QMouseEvent *)),widget, SLOT(rescaleAxes()));
    // Add Graph and s e t some p r o p e r t i e s
    widget->xAxis->setLabel(X_label);
    widget->yAxis->setLabel(Y_label);
    widget->xAxis->grid()->setSubGridVisible(true);
}

