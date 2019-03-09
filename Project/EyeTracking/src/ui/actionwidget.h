#ifndef ACTIONWIDGET_H
#define ACTIONWIDGET_H

#include <QWidget>
#include "icontrol.h"


class Control;
class QTimer;
class IControl;

namespace Ui {
class ActionWidget;
}
/*!
 * \brief The ActionWidget class    Widget resposible to change the background images when looking
 *                                  at a certain direction
 */
class ActionWidget : public QWidget,public IControl
{
    Q_OBJECT

public:
    /*!
     * \brief ActionWidget          contructor, variable initialize by initialization list
     * \param parent                QWidget parent
     * \param CamOp                 paremeter transmetted to the control classe
     * \param calibrationLeft       point of calibration of left eye
     * \param calibrationRight      point of calibration of right eye
     */
    explicit ActionWidget(QWidget *parent = nullptr,const std::string &CamOp = "WebCam",const cv::Point &calibrationLeft = cv::Point(0,0),const cv::Point &calibrationRight=cv::Point(0,0));
    ~ActionWidget() override;

    /*!
     * \brief displayMsg        show message tag + msg
     * \param tag               string to be shown first
     * \param msg               string to be shown second
     */
    void displayMsg(const std::string &tag, const std::string &msg) override;

    /*!
     * \brief setData       update the value of m_lastData
     * \param data          new vlaue of m_lasData
     */
    void setData(DataBufferPtr data) override;

    /*!
     * \brief setPoint
     * \param eyeLeft
     * \param eyeRight
     */
    void setPoint(const cv::Point &eyeLeft,const cv::Point &eyeRight) override;

    /*!
     * \brief myShow            show the widget in full scale
     */
    void myShow();

    /*!
     * \brief setBackground     change the image in background
     * \param newImage          new background image
     */
    void setBackground(QPixmap newImage);

private:
    Ui::ActionWidget *ui;

    /*!
     * \brief m_calibrationEyeLeft      calibration point of left eye
     */
    cv::Point m_calibrationEyeLeft;

    /*!
     * \brief m_calibrationEyeRight     calibration point of right eye
     */
    cv::Point m_calibrationEyeRight;

    /*!
     * \brief m_lastData    DataBuffer tat contain the last data
     */
    std::shared_ptr<DataBuffer> m_lastData;

    /*!
     * \brief m_appCtrl     unique poiter to Control
     */
    std::unique_ptr<Control> m_appCtrl;

    /*!
     * \brief m_UpdateTimer
     */
    std::unique_ptr<QTimer> m_UpdateTimer;

    /*!
     * \brief m_UpdateRateMS        update time of background image
     */
    const int m_UpdateRateMS;

private slots:

    /*!
     * \brief buttonBack    stop control and emit back signal
     */
    void buttonBack();

    /*!
     * \brief Update    update background image
     */
    void Update();

signals:
    /*!
     * \brief back      signal for mainwindow
     */
    void back();

};

#endif // ACTIONWIDGET_H
