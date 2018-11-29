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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ActionWidget
{
public:
    QPushButton *BackButton;

    void setupUi(QWidget *ActionWidget)
    {
        if (ActionWidget->objectName().isEmpty())
            ActionWidget->setObjectName(QStringLiteral("ActionWidget"));
        ActionWidget->resize(400, 300);
        BackButton = new QPushButton(ActionWidget);
        BackButton->setObjectName(QStringLiteral("BackButton"));
        BackButton->setGeometry(QRect(330, 240, 61, 51));

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
