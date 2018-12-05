/********************************************************************************
** Form generated from reading UI file 'calibrationwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALIBRATIONWIDGET_H
#define UI_CALIBRATIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CalibrationWidget
{
public:
    QPushButton *RefuseButton;
    QPushButton *AcceptButton;

    void setupUi(QWidget *CalibrationWidget)
    {
        if (CalibrationWidget->objectName().isEmpty())
            CalibrationWidget->setObjectName(QStringLiteral("CalibrationWidget"));
        CalibrationWidget->resize(525, 347);
        CalibrationWidget->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        RefuseButton = new QPushButton(CalibrationWidget);
        RefuseButton->setObjectName(QStringLiteral("RefuseButton"));
        RefuseButton->setEnabled(true);
        RefuseButton->setGeometry(QRect(20, 95, 251, 61));
        QFont font;
        font.setPointSize(12);
        RefuseButton->setFont(font);
        RefuseButton->setAutoFillBackground(false);
        RefuseButton->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
"border-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"));
        RefuseButton->setCheckable(true);
        AcceptButton = new QPushButton(CalibrationWidget);
        AcceptButton->setObjectName(QStringLiteral("AcceptButton"));
        AcceptButton->setEnabled(true);
        AcceptButton->setGeometry(QRect(20, 190, 251, 61));
        AcceptButton->setFont(font);
        AcceptButton->setAutoFillBackground(false);
        AcceptButton->setStyleSheet(QLatin1String("background-color: rgb(0, 0, 0);\n"
"border-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"));
        AcceptButton->setCheckable(true);

        retranslateUi(CalibrationWidget);

        QMetaObject::connectSlotsByName(CalibrationWidget);
    } // setupUi

    void retranslateUi(QWidget *CalibrationWidget)
    {
        CalibrationWidget->setWindowTitle(QApplication::translate("CalibrationWidget", "Form", nullptr));
        RefuseButton->setText(QApplication::translate("CalibrationWidget", "Refuse Calibration", nullptr));
        AcceptButton->setText(QApplication::translate("CalibrationWidget", "Accept Calibration", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CalibrationWidget: public Ui_CalibrationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALIBRATIONWIDGET_H
