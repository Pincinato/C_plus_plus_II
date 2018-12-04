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

class CalibrationWidget : public QWidget,IControl
{
    Q_OBJECT

public:
    explicit CalibrationWidget(QWidget *parent = nullptr,ICalibrationWidget *owner = nullptr,const string &CamOp = "WebCam");
    ~CalibrationWidget() override;
    void displayMsg(const std::string &tag, const std::string &msg) override;
    void setData(DataBufferPtr data) override;
    void setPoint(const cv::Point &eyeLeft,const cv::Point &eyeRight) override;

    void myShow();
    void setBackground(QPixmap newImage);
    void enableButtons(bool op);
    void setCamoption( const string &CamOp);

private:
    Ui::CalibrationWidget *ui;
    std::shared_ptr<DataBuffer> m_lastData;
    std::unique_ptr<Control> m_appCtrl;
    string m_CamOption;
    ICalibrationWidget *m_owner;

private slots:
    void keyPressEvent(QKeyEvent *ev) override;
    void Accept();
    void Refuse();
signals:
    void back();
};

#endif // CALIBRATIONWIDGET_H
