#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "qcustomplot.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void plotData (const std::function<double(double)> &function1,const std::function<double(double)> &function2);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
