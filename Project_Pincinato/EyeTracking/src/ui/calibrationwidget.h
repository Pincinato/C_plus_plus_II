#ifndef CALIBRATIONWIDGET_H
#define CALIBRATIONWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include "dataBuffer.h"
#include "icontrol.h"
#include "control.h"
#include "icalibrationwidget.h"

namespace Ui {
class CalibrationWidget;
}

/*!
 * \brief The CalibrationWidget class
 */
class CalibrationWidget : public QWidget,IControl
{
    Q_OBJECT

public:
    /*!
     * \brief CalibrationWidget
     * \param parent
     * \param owner
     * \param CamOp
     */
    explicit CalibrationWidget(QWidget *parent = nullptr,ICalibrationWidget *owner = nullptr,const string &CamOp = "WebCam");
    ~CalibrationWidget() override;

    /*!
     * \brief displayMsg
     * \param tag
     * \param msg
     */
    void displayMsg(const std::string &tag, const std::string &msg) override;

    /*!
     * \brief setData
     * \param data
     */
    void setData(DataBufferPtr data) override;

    /*!
     * \brief setPoint
     * \param eyeLeft
     * \param eyeRight
     */
    void setPoint(const cv::Point &eyeLeft,const cv::Point &eyeRight) override;

    /*!
     * \brief myShow
     */
    void myShow();

    /*!
     * \brief setBackground
     * \param newImage
     */
    void setBackground(QPixmap newImage);

    /*!
     * \brief enableButtons
     * \param op
     */
    void enableButtons(bool op);
    //void setCamoption( const string &CamOp);

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
     * \brief keyPressEvent
     * \param ev
     */
    void keyPressEvent(QKeyEvent *ev) override;

    /*!
     * \brief Accept
     */
    void Accept();

    /*!
     * \brief Refuse
     */
    void Refuse();
signals:
    /*!
     * \brief back
     */
    void back();
};

#endif // CALIBRATIONWIDGET_H
