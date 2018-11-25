#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QWidget>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPixmap>
#include <QCloseEvent>
#include <QMessageBox>

#include <opencv2/opencv.hpp>
#include "ieye_detector.h"
#include "eye_detector.h"

namespace Ui {
class configWindow;
}

class configWindow : public QWidget, Ieye_detector
{
    Q_OBJECT

public:
    explicit configWindow(QWidget *parent = nullptr);
    ~configWindow();
    void setData(Mat frame);
    void setStatus(string cameraStatus);
    void print(Mat frame);

private:
    Ui::configWindow *ui;
    QGraphicsPixmapItem pixmap;
    unique_ptr<Eye_detector> detector;
private slots:
    void start();
    void stop();
};

#endif // CONFIGWINDOW_H
