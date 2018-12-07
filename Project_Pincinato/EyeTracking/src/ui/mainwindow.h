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
/*!
 * \brief The MainWindow class
 */
class MainWindow : public QWidget, ICalibrationWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow()override;

    /*!
     * \brief setCalibrationPoint
     * \param eyeLeft
     * \param eyeRight
     */
    void setCalibrationPoint(const cv::Point &eyeLeft,const cv::Point &eyeRight) override;

    /*!
     * \brief initEyeDetection
     */
    void  initEyeDetection();

    /*!
     * \brief initActionWidget
     */
    void  initActionWidget();

    /*!
     * \brief initCalibration
     */
    void  initCalibration();

    /*!
     * \brief myShow
     */
    void  myShow();
private:
    Ui::MainWindow *ui;

    /*!
     * \brief eyeDetectionWidget
     */
    unique_ptr<Widget> eyeDetectionWidget;

    /*!
     * \brief calibrator
     */
    unique_ptr<CalibrationWidget> calibrator;

    /*!
     * \brief m_actionWigdet
     */
    unique_ptr<ActionWidget> m_actionWigdet;

    /*!
     * \brief m_calibrationEyeRight
     */
    cv::Point m_calibrationEyeRight;

    /*!
     * \brief m_calibrationEyeLeft
     */
    cv::Point m_calibrationEyeLeft;

    /*!
     * \brief m_CamOption
     */
    string m_CamOption;

    /*!
     * \brief m_Iscalibrated
     */
    bool m_Iscalibrated;


private slots:

    /*!
     * \brief start
     */
    void start();

    /*!
     * \brief calibration
     */
    void calibration();

    /*!
     * \brief eyeDetectionView
     */
    void eyeDetectionView();

    /*!
     * \brief backEyeDetectionView
     */
    void backEyeDetectionView();

    /*!
     * \brief backCalibrationView
     */
    void backCalibrationView();

    /*!
     * \brief backActionView
     */
    void backActionView();

};

#endif // MAINWINDOW_H
