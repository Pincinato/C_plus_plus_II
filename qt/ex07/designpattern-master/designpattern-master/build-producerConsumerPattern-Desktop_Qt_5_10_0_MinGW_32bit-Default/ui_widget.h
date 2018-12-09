/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QComboBox *CameraOption;
    QPushButton *play_pushButton;
    QSlider *frameRateSlider;
    QSpacerItem *verticalSpacer;
    QLabel *frameRate_label;
    QWidget *videoWidgetHolder;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(1104, 622);
        verticalLayout_2 = new QVBoxLayout(Widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        CameraOption = new QComboBox(Widget);
        CameraOption->addItem(QString());
        CameraOption->addItem(QString());
        CameraOption->setObjectName(QStringLiteral("CameraOption"));

        verticalLayout->addWidget(CameraOption);

        play_pushButton = new QPushButton(Widget);
        play_pushButton->setObjectName(QStringLiteral("play_pushButton"));
        play_pushButton->setMinimumSize(QSize(81, 81));
        play_pushButton->setMaximumSize(QSize(81, 81));
        play_pushButton->setBaseSize(QSize(0, 0));

        verticalLayout->addWidget(play_pushButton);

        frameRateSlider = new QSlider(Widget);
        frameRateSlider->setObjectName(QStringLiteral("frameRateSlider"));
        frameRateSlider->setMinimum(0);
        frameRateSlider->setOrientation(Qt::Vertical);

        verticalLayout->addWidget(frameRateSlider);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        frameRate_label = new QLabel(Widget);
        frameRate_label->setObjectName(QStringLiteral("frameRate_label"));
        frameRate_label->setMaximumSize(QSize(150, 150));

        verticalLayout->addWidget(frameRate_label);


        horizontalLayout->addLayout(verticalLayout);

        videoWidgetHolder = new QWidget(Widget);
        videoWidgetHolder->setObjectName(QStringLiteral("videoWidgetHolder"));

        horizontalLayout->addWidget(videoWidgetHolder);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        CameraOption->setItemText(0, QApplication::translate("Widget", "VCamera", nullptr));
        CameraOption->setItemText(1, QApplication::translate("Widget", "RGBCamera", nullptr));

        play_pushButton->setText(QApplication::translate("Widget", "Play", nullptr));
        frameRate_label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
