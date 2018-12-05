/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QPushButton *Exit;
    QSplitter *splitter;
    QPushButton *Start;
    QPushButton *Calibration;
    QPushButton *EyeDetection;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(794, 536);
        Exit = new QPushButton(MainWindow);
        Exit->setObjectName(QStringLiteral("Exit"));
        Exit->setGeometry(QRect(630, 480, 141, 51));
        splitter = new QSplitter(MainWindow);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setGeometry(QRect(350, 140, 251, 291));
        splitter->setOrientation(Qt::Vertical);
        splitter->setHandleWidth(60);
        Start = new QPushButton(splitter);
        Start->setObjectName(QStringLiteral("Start"));
        splitter->addWidget(Start);
        Calibration = new QPushButton(splitter);
        Calibration->setObjectName(QStringLiteral("Calibration"));
        splitter->addWidget(Calibration);
        EyeDetection = new QPushButton(splitter);
        EyeDetection->setObjectName(QStringLiteral("EyeDetection"));
        splitter->addWidget(EyeDetection);

        retranslateUi(MainWindow);
        QObject::connect(Exit, SIGNAL(clicked()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Form", nullptr));
        Exit->setText(QApplication::translate("MainWindow", "Exit", nullptr));
        Start->setText(QApplication::translate("MainWindow", "Start Eye Tracking", nullptr));
        Calibration->setText(QApplication::translate("MainWindow", "Calibration", nullptr));
        EyeDetection->setText(QApplication::translate("MainWindow", "Eye Detection View", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
