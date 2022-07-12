/********************************************************************************
** Form generated from reading UI file 'dialogairfoildesigner.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGAIRFOILDESIGNER_H
#define UI_DIALOGAIRFOILDESIGNER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogAirfoilDesigner
{
public:
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout;
    QScrollArea *scrollArea_CONTROL_WIDGET;
    QWidget *scrollAreaWidgetContents_2;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit_CHORD_LENGTH;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *lineEdit_CAMBER;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *lineEdit_MAX_THICKNESS;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *lineEdit_ORDER;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QLineEdit *lineEdit_NO_KNOTS;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *pushButton_READ_ANCHORS;
    QPushButton *pushButton_APPLY_READ_ANCHORS;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButton_APPLY_FULL;
    QPushButton *pushButton_CANCEL;
    QPushButton *pushButton_CLOSE;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer_2;
    QWidget *widget_SCREEN;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea_GRAPHICS_WINDOW;
    QWidget *scrollAreaWidgetContents;
    QTextEdit *textEdit_CONSOLE_WINDOW;

    void setupUi(QDialog *DialogAirfoilDesigner)
    {
        if (DialogAirfoilDesigner->objectName().isEmpty())
            DialogAirfoilDesigner->setObjectName(QString::fromUtf8("DialogAirfoilDesigner"));
        DialogAirfoilDesigner->resize(878, 508);
        gridLayout_3 = new QGridLayout(DialogAirfoilDesigner);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(5, -1, 5, -1);
        scrollArea_CONTROL_WIDGET = new QScrollArea(DialogAirfoilDesigner);
        scrollArea_CONTROL_WIDGET->setObjectName(QString::fromUtf8("scrollArea_CONTROL_WIDGET"));
        scrollArea_CONTROL_WIDGET->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 319, 465));
        gridLayout = new QGridLayout(scrollAreaWidgetContents_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 5, -1, 5);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(5, -1, 5, -1);
        label = new QLabel(scrollAreaWidgetContents_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        lineEdit_CHORD_LENGTH = new QLineEdit(scrollAreaWidgetContents_2);
        lineEdit_CHORD_LENGTH->setObjectName(QString::fromUtf8("lineEdit_CHORD_LENGTH"));

        horizontalLayout_2->addWidget(lineEdit_CHORD_LENGTH);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(5, -1, 5, -1);
        label_2 = new QLabel(scrollAreaWidgetContents_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        lineEdit_CAMBER = new QLineEdit(scrollAreaWidgetContents_2);
        lineEdit_CAMBER->setObjectName(QString::fromUtf8("lineEdit_CAMBER"));

        horizontalLayout_3->addWidget(lineEdit_CAMBER);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(5, -1, 5, -1);
        label_3 = new QLabel(scrollAreaWidgetContents_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_4->addWidget(label_3);

        lineEdit_MAX_THICKNESS = new QLineEdit(scrollAreaWidgetContents_2);
        lineEdit_MAX_THICKNESS->setObjectName(QString::fromUtf8("lineEdit_MAX_THICKNESS"));

        horizontalLayout_4->addWidget(lineEdit_MAX_THICKNESS);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(5, -1, 5, -1);
        label_4 = new QLabel(scrollAreaWidgetContents_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        lineEdit_ORDER = new QLineEdit(scrollAreaWidgetContents_2);
        lineEdit_ORDER->setObjectName(QString::fromUtf8("lineEdit_ORDER"));

        horizontalLayout_5->addWidget(lineEdit_ORDER);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(5, -1, 5, -1);
        label_5 = new QLabel(scrollAreaWidgetContents_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_6->addWidget(label_5);

        lineEdit_NO_KNOTS = new QLineEdit(scrollAreaWidgetContents_2);
        lineEdit_NO_KNOTS->setObjectName(QString::fromUtf8("lineEdit_NO_KNOTS"));

        horizontalLayout_6->addWidget(lineEdit_NO_KNOTS);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        pushButton_READ_ANCHORS = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_READ_ANCHORS->setObjectName(QString::fromUtf8("pushButton_READ_ANCHORS"));

        horizontalLayout_8->addWidget(pushButton_READ_ANCHORS);

        pushButton_APPLY_READ_ANCHORS = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_APPLY_READ_ANCHORS->setObjectName(QString::fromUtf8("pushButton_APPLY_READ_ANCHORS"));

        horizontalLayout_8->addWidget(pushButton_APPLY_READ_ANCHORS);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_7);


        verticalLayout_2->addLayout(horizontalLayout_8);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        pushButton_APPLY_FULL = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_APPLY_FULL->setObjectName(QString::fromUtf8("pushButton_APPLY_FULL"));

        horizontalLayout_7->addWidget(pushButton_APPLY_FULL);

        pushButton_CANCEL = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_CANCEL->setObjectName(QString::fromUtf8("pushButton_CANCEL"));

        horizontalLayout_7->addWidget(pushButton_CANCEL);

        pushButton_CLOSE = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_CLOSE->setObjectName(QString::fromUtf8("pushButton_CLOSE"));

        horizontalLayout_7->addWidget(pushButton_CLOSE);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_6);


        verticalLayout_2->addLayout(horizontalLayout_7);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);

        scrollArea_CONTROL_WIDGET->setWidget(scrollAreaWidgetContents_2);

        horizontalLayout->addWidget(scrollArea_CONTROL_WIDGET);

        widget_SCREEN = new QWidget(DialogAirfoilDesigner);
        widget_SCREEN->setObjectName(QString::fromUtf8("widget_SCREEN"));
        gridLayout_2 = new QGridLayout(widget_SCREEN);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 5, -1, 5);
        scrollArea_GRAPHICS_WINDOW = new QScrollArea(widget_SCREEN);
        scrollArea_GRAPHICS_WINDOW->setObjectName(QString::fromUtf8("scrollArea_GRAPHICS_WINDOW"));
        scrollArea_GRAPHICS_WINDOW->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 611, 339));
        scrollArea_GRAPHICS_WINDOW->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea_GRAPHICS_WINDOW);

        textEdit_CONSOLE_WINDOW = new QTextEdit(widget_SCREEN);
        textEdit_CONSOLE_WINDOW->setObjectName(QString::fromUtf8("textEdit_CONSOLE_WINDOW"));

        verticalLayout->addWidget(textEdit_CONSOLE_WINDOW);

        verticalLayout->setStretch(0, 3);
        verticalLayout->setStretch(1, 1);

        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);


        horizontalLayout->addWidget(widget_SCREEN);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 3);

        gridLayout_3->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(DialogAirfoilDesigner);

        QMetaObject::connectSlotsByName(DialogAirfoilDesigner);
    } // setupUi

    void retranslateUi(QDialog *DialogAirfoilDesigner)
    {
        DialogAirfoilDesigner->setWindowTitle(QCoreApplication::translate("DialogAirfoilDesigner", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("DialogAirfoilDesigner", "Chord Length :", nullptr));
        label_2->setText(QCoreApplication::translate("DialogAirfoilDesigner", "Camber (%c):", nullptr));
        label_3->setText(QCoreApplication::translate("DialogAirfoilDesigner", "Max Thickness (%c):", nullptr));
        label_4->setText(QCoreApplication::translate("DialogAirfoilDesigner", "Order:", nullptr));
        label_5->setText(QCoreApplication::translate("DialogAirfoilDesigner", "No. Knots:", nullptr));
        pushButton_READ_ANCHORS->setText(QCoreApplication::translate("DialogAirfoilDesigner", "Read Anchors", nullptr));
        pushButton_APPLY_READ_ANCHORS->setText(QCoreApplication::translate("DialogAirfoilDesigner", "Apply", nullptr));
        pushButton_APPLY_FULL->setText(QCoreApplication::translate("DialogAirfoilDesigner", "Apply", nullptr));
        pushButton_CANCEL->setText(QCoreApplication::translate("DialogAirfoilDesigner", "Cancel", nullptr));
        pushButton_CLOSE->setText(QCoreApplication::translate("DialogAirfoilDesigner", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogAirfoilDesigner: public Ui_DialogAirfoilDesigner {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGAIRFOILDESIGNER_H
