#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <memory>
#include "icalibrationwidget.h"

class QWidget;
class CalibrationWidget;
class Widget;
class ICalibrationWidget;
class ActionWidget;

namespace Ui {
class MainWindow;
}
/*!
 * \brief The MainWindow class      controls tha change of widget
 */
class MainWindow : public QWidget, ICalibrationWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow()override;

    /*!
     * \brief setCalibrationPoint       set calibraion point of left and right eye
     * \param eyeLeft                   Point at the center of left eye
     * \param eyeRight                  Point at the center of right eye
     */
    void setCalibrationPoint(const cv::Point &eyeLeft,const cv::Point &eyeRight) override;

    /*!
     * \brief initEyeDetection      initialize widget - widget
     */
    void  initEyeDetection();

    /*!
     * \brief initActionWidget      initialize Action Widget
     */
    void  initActionWidget();

    /*!
     * \brief initCalibration       initialize Calibration widget
     */
    void  initCalibration();

    /*!
     * \brief myShow                show this widget in full scale
     */
    void  myShow();
private:
    Ui::MainWindow *ui;

    /*!
     * \brief eyeDetectionWidget
     */
    std::unique_ptr<Widget> eyeDetectionWidget;

    /*!
     * \brief calibrator
     */
    std::unique_ptr<CalibrationWidget> m_calibrator;

    /*!
     * \brief m_actionWigdet
     */
    std::unique_ptr<ActionWidget> m_actionWigdet;

    /*!
     * \brief m_calibrationEyeRight     calibration point of right eye
     */
    cv::Point m_calibrationEyeRight;

    /*!
     * \brief m_calibrationEyeLeft      calibration point of left eye
     */
    cv::Point m_calibrationEyeLeft;

    /*!
     * \brief m_CamOption       string that indicates the camera option
     */
    std::string m_CamOption;

    /*!
     * \brief m_Iscalibrated    state of calibration
     */
    bool m_Iscalibrated;


private slots:

    /*!
     * \brief start     connected with start button, show action widget
     */
    void start();

    /*!
     * \brief calibration       connected with calibration button, show calibration widget
     */
    void calibration();

    /*!
     * \brief eyeDetectionView  connected with eyeDetection button, show eyeDetection widget
     */
    void eyeDetectionView();

    /*!
     * \brief backEyeDetectionView  close EyeDetection widget
     */
    void backEyeDetectionView();

    /*!
     * \brief backCalibrationView       close Calibration widget
     */
    void backCalibrationView();

    /*!
     * \brief backActionView            close Action widget
     */
    void backActionView();

};

#endif // MAINWINDOW_H
