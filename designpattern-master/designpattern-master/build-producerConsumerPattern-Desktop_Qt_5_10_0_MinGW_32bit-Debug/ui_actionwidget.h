/********************************************************************************
** Form generated from reading UI file 'actionwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACTIONWIDGET_H
#define UI_ACTIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ActionWidget
{
public:
    QPushButton *BackButton;
    QSlider *SensibilitySlider;

    void setupUi(QWidget *ActionWidget)
    {
        if (ActionWidget->objectName().isEmpty())
            ActionWidget->setObjectName(QStringLiteral("ActionWidget"));
        ActionWidget->setWindowModality(Qt::NonModal);
        ActionWidget->resize(200, 215);
        BackButton = new QPushButton(ActionWidget);
        BackButton->setObjectName(QStringLiteral("BackButton"));
        BackButton->setGeometry(QRect(80, 30, 70, 81));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(BackButton->sizePolicy().hasHeightForWidth());
        BackButton->setSizePolicy(sizePolicy);
        SensibilitySlider = new QSlider(ActionWidget);
        SensibilitySlider->setObjectName(QStringLiteral("SensibilitySlider"));
        SensibilitySlider->setGeometry(QRect(30, 10, 11, 185));
        SensibilitySlider->setMinimum(0);
        SensibilitySlider->setOrientation(Qt::Vertical);

        retranslateUi(ActionWidget);

        QMetaObject::connectSlotsByName(ActionWidget);
    } // setupUi

    void retranslateUi(QWidget *ActionWidget)
    {
        ActionWidget->setWindowTitle(QApplication::translate("ActionWidget", "Form", nullptr));
        BackButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ActionWidget: public Ui_ActionWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACTIONWIDGET_H
