#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "widget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Widget * eyeDetectionWidget;


private slots:

    void start();
    void calibration();
    void eyeDetectionView();
    void backEyeDetectionView();

};

#endif // MAINWINDOW_H
