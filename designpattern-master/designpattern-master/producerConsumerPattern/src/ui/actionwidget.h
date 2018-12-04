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

class ActionWidget : public QWidget,public IControl
{
    Q_OBJECT

public:
    explicit ActionWidget(QWidget *parent = nullptr,const string &CamOp = "WebCam",const Point &calibrationLeft = Point(0,0),const Point &calibrationRight=Point(0,0));
    ~ActionWidget() override;
    void displayMsg(const std::string &tag, const std::string &msg) override;
    void setData(DataBufferPtr data) override;
    void setPoint(const cv::Point &eyeLeft,const cv::Point &eyeRight) override;
    void myShow();
    void setCamOption(const string &Cam);
    void setBackground(QPixmap newImage);
    void setTemplate(const Mat &newEyetemplate);
private:
    Ui::ActionWidget *ui;
    cv::Point calibrationEyeLeft;
    Mat EyeTemplate;
    cv::Point calibrationEyeRight;
    string CamOption;
    std::shared_ptr<DataBuffer> m_lastData;
    std::unique_ptr<Control> m_appCtrl;
    std::unique_ptr<QTimer> m_UpdateTimer;
    const int m_UpdateRateMS;

private slots:
    void buttonBack();
    void Update();

signals:
    void back();

};

#endif // ACTIONWIDGET_H
