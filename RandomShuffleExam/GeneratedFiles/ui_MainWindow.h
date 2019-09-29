/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *locationLbl;
    QLineEdit *dirLedr;
    QPushButton *selectDirBtn;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *browseBtn;
    QPushButton *shuffleBtn;
    QSpacerItem *horizontalSpacer;
    QPushButton *applyBtn;
    QPushButton *cancelBtn;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(860, 640);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Resources/exam.svg"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindowClass->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        locationLbl = new QLabel(centralWidget);
        locationLbl->setObjectName(QStringLiteral("locationLbl"));

        horizontalLayout->addWidget(locationLbl);

        dirLedr = new QLineEdit(centralWidget);
        dirLedr->setObjectName(QStringLiteral("dirLedr"));

        horizontalLayout->addWidget(dirLedr);

        selectDirBtn = new QPushButton(centralWidget);
        selectDirBtn->setObjectName(QStringLiteral("selectDirBtn"));

        horizontalLayout->addWidget(selectDirBtn);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        browseBtn = new QPushButton(centralWidget);
        browseBtn->setObjectName(QStringLiteral("browseBtn"));

        horizontalLayout_2->addWidget(browseBtn);

        shuffleBtn = new QPushButton(centralWidget);
        shuffleBtn->setObjectName(QStringLiteral("shuffleBtn"));

        horizontalLayout_2->addWidget(shuffleBtn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        applyBtn = new QPushButton(centralWidget);
        applyBtn->setObjectName(QStringLiteral("applyBtn"));

        horizontalLayout_2->addWidget(applyBtn);

        cancelBtn = new QPushButton(centralWidget);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout_2->addWidget(cancelBtn);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        MainWindowClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", nullptr));
        locationLbl->setText(QApplication::translate("MainWindowClass", "L\306\260u v\303\240o:", nullptr));
        selectDirBtn->setText(QApplication::translate("MainWindowClass", "Ch\341\273\215n...", nullptr));
        browseBtn->setText(QApplication::translate("MainWindowClass", "Ch\341\273\215n b\303\240i thi", nullptr));
        shuffleBtn->setText(QApplication::translate("MainWindowClass", "T\341\272\241o ph\303\241ch", nullptr));
        applyBtn->setText(QApplication::translate("MainWindowClass", "\304\220\341\273\223ng \303\275", nullptr));
        cancelBtn->setText(QApplication::translate("MainWindowClass", "Tho\303\241t", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
