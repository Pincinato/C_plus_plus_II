#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "widget.h"
#include "calibrationwidget.h"
#include "icalibrationwidget.h"
#include "actionwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget, ICalibrationWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setCalibrationPoint(const cv::Point &eyeLeft,const cv::Point &eyeRight) override;
private:
    Ui::MainWindow *ui;
    unique_ptr<Widget> eyeDetectionWidget;
    unique_ptr<CalibrationWidget> calibrator;
    unique_ptr<ActionWidget> m_actionWigdet;
    cv::Point calibrationEyeRight;
    cv::Point calibrationEyeLeft;
    string CamOption;


private slots:

    void start();
    void calibration();
    void eyeDetectionView();
    void backEyeDetectionView();
    void backCalibrationView();
    void backActionView();

};

#endif // MAINWINDOW_H
