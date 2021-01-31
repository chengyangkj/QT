/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "animationstackedwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_9;
    QLabel *label_10;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_8;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_11;
    QLabel *label_12;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    AnimationStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout_2;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout;
    QWidget *widget_6;
    QWidget *page_2;
    QGridLayout *gridLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget_3;
    QWidget *widget_4;
    QWidget *widget_2;
    QWidget *page_3;
    QGridLayout *gridLayout_3;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget_8;
    QWidget *widget_9;
    QPushButton *pushButton_2;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(802, 509);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QLatin1String("QWidget#centralWidget{background-color: qlineargradient(spread:reflect, x1:0, y1:0, x2:0.61, y2:0.086, stop:0 rgba(46, 50, 83, 255), stop:0.751412 rgba(128, 50, 148, 255));border:0px solid red;\n"
"border-radius:6px;}\n"
""));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(5);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setMinimumSize(QSize(112, 35));
        label_9->setMaximumSize(QSize(112, 35));
        label_9->setStyleSheet(QString::fromUtf8("\n"
"font: 75 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 25, 25);"));
        label_9->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_9);

        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setMinimumSize(QSize(151, 35));
        label_10->setMaximumSize(QSize(151, 35));
        label_10->setStyleSheet(QString::fromUtf8("\n"
"font: 75 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(20, 255, 8);"));
        label_10->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_10);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMinimumSize(QSize(54, 16));
        label_8->setStyleSheet(QString::fromUtf8("\n"
"font: 75 20pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 25, 25);"));
        label_8->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_8);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setMinimumSize(QSize(152, 35));
        label_11->setMaximumSize(QSize(152, 35));
        label_11->setStyleSheet(QString::fromUtf8("\n"
"font: 75 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(20, 255, 8);"));
        label_11->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_11);

        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setMinimumSize(QSize(151, 35));
        label_12->setMaximumSize(QSize(151, 35));
        label_12->setStyleSheet(QString::fromUtf8("\n"
"font: 75 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(20, 255, 8);"));
        label_12->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_12);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(0, 200));
        pushButton->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/new/prefix1/Resourse/appbar.chevron.left.png);}\n"
"\n"
"QPushButton:hover{border-image: url(:/new/prefix1/Resourse/appbar.chevron.left.png);background-color: rgb(137, 255, 46,90);}\n"
""));

        horizontalLayout->addWidget(pushButton);

        stackedWidget = new AnimationStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setStyleSheet(QStringLiteral(""));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        page->setStyleSheet(QStringLiteral("background-color: rgb(200, 255, 17,0);"));
        gridLayout_2 = new QGridLayout(page);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        widget_5 = new QWidget(page);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        widget_5->setStyleSheet(QLatin1String("background-color: rgb(255, 85, 187);\n"
"border-radius:6px;"));
        verticalLayout = new QVBoxLayout(widget_5);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        gridLayout_2->addWidget(widget_5, 0, 0, 1, 1);

        widget_6 = new QWidget(page);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        widget_6->setStyleSheet(QLatin1String("background-color: rgb(83, 91, 255);\n"
"border-radius:6px;"));

        gridLayout_2->addWidget(widget_6, 1, 0, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        page_2->setStyleSheet(QStringLiteral("background-color: rgb(200, 255, 17,0);"));
        gridLayout = new QGridLayout(page_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget = new QWidget(page_2);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QLatin1String("background-color: rgb(83, 91, 255);\n"
"border-radius:6px;"));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));

        gridLayout->addWidget(widget, 0, 0, 1, 1);

        widget_3 = new QWidget(page_2);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setStyleSheet(QLatin1String("background-color: rgb(255, 16, 20);\n"
"border-radius:6px;"));

        gridLayout->addWidget(widget_3, 1, 0, 1, 1);

        widget_4 = new QWidget(page_2);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setStyleSheet(QLatin1String("background-color: rgb(12, 36, 255);\n"
"border-radius:6px;"));

        gridLayout->addWidget(widget_4, 1, 1, 1, 1);

        widget_2 = new QWidget(page_2);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setStyleSheet(QLatin1String("background-color: rgb(255, 147, 133);\n"
"border-radius:6px;"));

        gridLayout->addWidget(widget_2, 0, 1, 1, 1);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        page_3->setStyleSheet(QStringLiteral("background-color: rgb(200, 255, 17,0);"));
        gridLayout_3 = new QGridLayout(page_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        widget_7 = new QWidget(page_3);
        widget_7->setObjectName(QStringLiteral("widget_7"));
        widget_7->setStyleSheet(QLatin1String("background-color: rgb(83, 91, 255);\n"
"border-radius:6px;"));
        horizontalLayout_3 = new QHBoxLayout(widget_7);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));

        gridLayout_3->addWidget(widget_7, 0, 0, 1, 1);

        widget_8 = new QWidget(page_3);
        widget_8->setObjectName(QStringLiteral("widget_8"));
        widget_8->setStyleSheet(QLatin1String("background-color: rgb(157, 255, 130);\n"
"border-radius:6px;"));

        gridLayout_3->addWidget(widget_8, 0, 1, 1, 1);

        widget_9 = new QWidget(page_3);
        widget_9->setObjectName(QStringLiteral("widget_9"));
        widget_9->setStyleSheet(QLatin1String("background-color: rgb(11, 255, 255);\n"
"border-radius:6px;"));

        gridLayout_3->addWidget(widget_9, 1, 0, 1, 2);

        stackedWidget->addWidget(page_3);

        horizontalLayout->addWidget(stackedWidget);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(0, 200));
        pushButton_2->setMaximumSize(QSize(16777215, 200));
        pushButton_2->setStyleSheet(QLatin1String("QPushButton{border-image: url(:/new/prefix1/Resourse/appbar.chevron.right.png);}\n"
"\n"
"QPushButton:hover{border-image: url(:/new/prefix1/Resourse/appbar.chevron.right.png);background-color: rgb(137, 255, 46,90);}\n"
""));

        horizontalLayout->addWidget(pushButton_2);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(5);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(54, 16));
        label_4->setMaximumSize(QSize(54, 16));
        label_4->setStyleSheet(QString::fromUtf8("background-color: rgba(24, 46, 58, 90);\n"
"font: 75 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 25, 25);"));
        label_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_4);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMinimumSize(QSize(54, 16));
        label_5->setMaximumSize(QSize(54, 16));
        label_5->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255,90);\n"
"color: rgb(255, 25, 25);\n"
"font: 75 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_5->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_5);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(54, 16));
        label_6->setMaximumSize(QSize(54, 16));
        label_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255,90);\n"
"color: rgb(255, 25, 25);\n"
"font: 75 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label_6->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_6);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_4);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "Author:Jecjiang", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "811365949@qq.com", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "\347\277\273\351\241\265\346\273\221\345\261\217", Q_NULLPTR));
        label_11->setText(QString());
        label_12->setText(QString());
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "2", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "3", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
