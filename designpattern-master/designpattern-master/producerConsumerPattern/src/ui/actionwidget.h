#ifndef ACTIONWIDGET_H
#define ACTIONWIDGET_H

#include <QWidget>
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
    explicit ActionWidget(QWidget *parent = nullptr,const string &CamOp = "WebCam");
    ~ActionWidget() override;
    void displayMsg(const std::string &tag, const std::string &msg) override;
    void setData(DataBufferPtr data) override;
    void setPoint(const cv::Point eye_center) override;
    void myShow();
    void setCamOption(const string &Cam);
private:
    Ui::ActionWidget *ui;
    string CamOption;
    std::shared_ptr<DataBuffer> m_lastData;
    std::unique_ptr<Control> m_appCtrl;


private slots:
    void buttonBack();

signals:
    void back();

};

#endif // ACTIONWIDGET_H
