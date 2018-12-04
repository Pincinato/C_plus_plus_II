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
    ~MainWindow()override;
    void setCalibrationPoint(const Mat &frame,const cv::Point &eyeLeft,const cv::Point &eyeRight) override;
    void  initEyeDetection();
    void  initActionWidget();
    void  initCalibration();
    void  myShow();
private:
    Ui::MainWindow *ui;
    unique_ptr<Widget> eyeDetectionWidget;
    unique_ptr<CalibrationWidget> calibrator;
    unique_ptr<ActionWidget> m_actionWigdet;
    cv::Point m_calibrationEyeRight;
    cv::Point m_calibrationEyeLeft;
    string m_CamOption;
    bool m_Iscalibrated;


private slots:

    void start();
    void calibration();
    void eyeDetectionView();
    void backEyeDetectionView();
    void backCalibrationView();
    void backActionView();

};

#endif // MAINWINDOW_H
