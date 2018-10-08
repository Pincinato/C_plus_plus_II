#ifndef WIDGET_EX3_4_H
#define WIDGET_EX3_4_H

#include <QWidget>
#include <fstream>
#include "qcustomplot.h"

namespace Ui {
class widget_ex3_4;
}

class widget_ex3_4 : public QWidget
{
    Q_OBJECT

public:
    explicit widget_ex3_4(QWidget *parent = nullptr);
    ~widget_ex3_4();
    void plotData(std::ifstream &in);
private slots:
    void handleButton(void);
private:
    Ui::widget_ex3_4 *ui;
    std::vector<std::pair<double,double>>find_peaks(const std::vector<double> &data,const uint window, const int threshold);
    void presetWindow(QcustomPlot * widget,QString Title, QString X_label,QString Y_label);

};

#endif // WIDGET_EX3_4_H
