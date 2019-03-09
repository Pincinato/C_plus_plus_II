#ifndef CALIBRATIONWIDGET_H
#define CALIBRATIONWIDGET_H

#include <QWidget>
#include "icontrol.h"
#include "icalibrationwidget.h"

class DataBuffer;
class Control;
class QKeyEvent;

namespace Ui {
class CalibrationWidget;
}

/*!
 * \brief The CalibrationWidget     reponsible to get the calibration of left and right eye
 */
class CalibrationWidget : public QWidget,IControl
{
    Q_OBJECT

public:
    /*!
     * \brief CalibrationWidget     Constructor, variables are initialize with initialize list
     * \param parent
     * \param owner                 unique pointer to ICalibrationWidget
     * \param CamOp
     */
    explicit CalibrationWidget(QWidget *parent = nullptr,ICalibrationWidget *owner = nullptr,const std::string &CamOp = "WebCam");
    ~CalibrationWidget() override;

    /*!
     * \brief displayMsg       display tag and msg
     * \param tag              first string to be displyed
     * \param msg              second string to be displyed
     */
    void displayMsg(const std::string &tag, const std::string &msg) override;

    /*!
     * \brief setData           update of m_lastData
     * \param data              new m_lastData
     */
    void setData(DataBufferPtr data) override;

    /*!
     * \brief setPoint      set calibration points
     * \param eyeLeft       new left eye calibration
     * \param eyeRight      new right eye calibration
     */
    void setPoint(const cv::Point &eyeLeft,const cv::Point &eyeRight) override;

    /*!
     * \brief myShow        show widget in full scale and postion of object
     */
    void myShow();

    /*!
     * \brief setBackground     change background image
     * \param newImage          new background image
     */
    void setBackground(QPixmap newImage);

    /*!
     * \brief enableButtons     enable or disable button in the widget
     * \param op                bool parameter, with true enable button
     *                          If false, disable button
     */
    void enableButtons(bool op);

private:
    Ui::CalibrationWidget *ui;

    /*!
     * \brief m_lastData
     */
    std::shared_ptr<DataBuffer> m_lastData;

    /*!
     * \brief m_appCtrl
     */
    std::unique_ptr<Control> m_appCtrl;
    //string m_CamOption;

    /*!
     * \brief m_owner
     */
    ICalibrationWidget *m_owner;

private slots:

    /*!
     * \brief keyPressEvent     event to detect keyboard actions
     * \param ev                the keyboard button pushed
     */
    void keyPressEvent(QKeyEvent *ev) override;

    /*!
     * \brief Accept        emit back() signal
     */
    void Accept();

    /*!
     * \brief Refuse        change background image and restart control
     */
    void Refuse();
signals:
    /*!
     * \brief back
     */
    void back();
};

#endif // CALIBRATIONWIDGET_H
