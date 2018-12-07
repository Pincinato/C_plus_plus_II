#ifndef ACTIONWIDGET_H
#define ACTIONWIDGET_H

#include <QWidget>
#include <QTimer>
#include <string>
#include "icontrol.h"
#include "control.h"

using namespace std;

namespace Ui {
class ActionWidget;
}
/*!
 * \brief The ActionWidget class
 */
class ActionWidget : public QWidget,public IControl
{
    Q_OBJECT

public:
    /*!
     * \brief ActionWidget
     * \param parent
     * \param CamOp
     * \param calibrationLeft
     * \param calibrationRight
     */
    explicit ActionWidget(QWidget *parent = nullptr,const string &CamOp = "WebCam",const Point &calibrationLeft = Point(0,0),const Point &calibrationRight=Point(0,0));
    ~ActionWidget() override;

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
     * \brief setCamOption
     * \param Cam
     */
    void setCamOption(const string &Cam);

    /*!
     * \brief setBackground
     * \param newImage
     */
    void setBackground(QPixmap newImage);

private:
    Ui::ActionWidget *ui;

    /*!
     * \brief m_calibrationEyeLeft
     */
    cv::Point m_calibrationEyeLeft;

    /*!
     * \brief m_calibrationEyeRight
     */
    cv::Point m_calibrationEyeRight;

    /*!
     * \brief m_CamOption
     */
    string m_CamOption;

    /*!
     * \brief m_lastData
     */
    std::shared_ptr<DataBuffer> m_lastData;

    /*!
     * \brief m_appCtrl
     */
    std::unique_ptr<Control> m_appCtrl;

    /*!
     * \brief m_UpdateTimer
     */
    std::unique_ptr<QTimer> m_UpdateTimer;

    /*!
     * \brief m_UpdateRateMS
     */
    const int m_UpdateRateMS;

private slots:

    /*!
     * \brief buttonBack
     */
    void buttonBack();

    /*!
     * \brief Update
     */
    void Update();

signals:
    /*!
     * \brief back
     */
    void back();

};

#endif // ACTIONWIDGET_H
