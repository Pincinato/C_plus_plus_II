/****************************************************************************
** Copyright (c) 2018 HuCE-optoLab - Bern University of Applied Science
** Project: Example of a producer-comsumer-pattern
**
** Contact:    Patrik Arnold ( patrik.arnold@bfh.ch )
*****************************************************************************/
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <memory>
#include "icontrol.h"

// Forward declarations
class DataBuffer;
class IControl;
class Control;
class VideoVisualizer;
class QTimer;
class QWidget;


namespace Ui {
class Widget;
}

/*!
 * \brief The Widget class
 */

class Widget : public QWidget, IControl
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget() override;

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
     * \brief getCamOption
     * \return
     */
    std::string getCamOption();

    /*!
     * \brief setPoint
     * \param eyeLeft
     * \param eyeRight
     */
    void setPoint(const cv::Point &eyeLeft,const cv::Point &eyeRight) override;

    /*!
     * \brief myShow        show image in full screen and set background
     */
    void myShow();
private:
    /*!
     * \brief initGUI
     */
    void initGUI();

    /*!
     * \brief updateScanVis
     */
    void updateScanVis();

private slots:
    /*!
     * \brief updateGui
     */
    void updateGui();

    /*!
     * \brief updateFrameRate
     */
    void updateFrameRate();

    /*!
     * \brief playDataFromFile
     */
    void playDataFromFile();

    /*!
     * \brief setPlayRate
     */
    void setPlayRate();

    /*!
     * \brief setCamera
     * \param text
     */
    void setCamera(const QString & text);

private:

    void updateCameraOptions(const size_t &numberCamera);

    Ui::Widget* ui;
    /*!
     * \brief m_tag
     */
    QString m_tag;

    /*!
     * \brief m_lastData
     */
    std::shared_ptr<DataBuffer> m_lastData;
    //std::unique_ptr<Control> m_appCtrl;

    /*!
     * \brief m_appCtrl
     */
    std::unique_ptr<Control> m_appCtrl;

    /*!
     * \brief m_videoVisualizer
     */
    std::unique_ptr<VideoVisualizer> m_videoVisualizer;

    /*!
     * \brief m_guiUpdateTimer
     */
    std::unique_ptr<QTimer> m_guiUpdateTimer;

    /*!
     * \brief m_frameRateTimer
     */
    std::unique_ptr<QTimer> m_frameRateTimer;

    /*!
     * \brief m_CamOption
     */
    std::string m_CamOption;

    /*!
     * \brief m_frameCount
     */
    size_t m_frameCount;

    /*!
     * \brief m_GuiUpdateRateMS
     */
    const size_t m_GuiUpdateRateMS;

    /*!
     * \brief m_fpsUpdateRateMS
     */
    const size_t m_fpsUpdateRateMS;

    /*!
     * \brief m_numberOfActualCamera
     */
    size_t m_numberOfActualCamera;

private slots:

     /*!
     * \brief sendBack
     */
    void sendBack();

signals:

    /*!
     * \brief back
     */
    void back();

};

#endif // WIDGET_H
