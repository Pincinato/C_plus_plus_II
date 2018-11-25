#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include "qcustomplot.h"
#include "eye_detector.h"
#include "ieye_detector.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget, Ieye_detector
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void setData(Mat &frame);
    void setStatus(string cameraStatus);
    void print(Mat &frame);

private:
    Ui::Widget *ui;
    QGraphicsPixmapItem pixmap;
    unique_ptr<Eye_detector> detector;
    unique_ptr<QTimer> m_UpdateTimer;
    Mat frame;

private slots:
    void start();
    void stop();
    void updateWidget();
};

#endif // WIDGET_H
