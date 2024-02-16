/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "gldisplaywidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    GLDisplayWidget *maillage;
    QPushButton *Maillage;
    QPushButton *Import_Mesh;
    QPushButton *Save_Mesh;
    QPushButton *Color;
    QSpinBox *Sommet;
    QPushButton *Quit;
    QCheckBox *WireFrame;
    QPushButton *Laplacian;
    QGroupBox *Param_L;
    QRadioButton *Position;
    QRadioButton *Courbure;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(747, 528);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        maillage = new GLDisplayWidget(centralWidget);
        maillage->setObjectName("maillage");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(maillage->sizePolicy().hasHeightForWidth());
        maillage->setSizePolicy(sizePolicy);
        Maillage = new QPushButton(maillage);
        Maillage->setObjectName("Maillage");
        Maillage->setGeometry(QRect(10, 20, 101, 31));
        Import_Mesh = new QPushButton(maillage);
        Import_Mesh->setObjectName("Import_Mesh");
        Import_Mesh->setGeometry(QRect(10, 60, 101, 31));
        Save_Mesh = new QPushButton(maillage);
        Save_Mesh->setObjectName("Save_Mesh");
        Save_Mesh->setGeometry(QRect(10, 100, 101, 31));
        Color = new QPushButton(maillage);
        Color->setObjectName("Color");
        Color->setGeometry(QRect(10, 140, 101, 31));
        Sommet = new QSpinBox(maillage);
        Sommet->setObjectName("Sommet");
        Sommet->setGeometry(QRect(130, 20, 51, 31));
        Sommet->setMaximum(100000);
        Quit = new QPushButton(maillage);
        Quit->setObjectName("Quit");
        Quit->setGeometry(QRect(10, 180, 101, 31));
        WireFrame = new QCheckBox(maillage);
        WireFrame->setObjectName("WireFrame");
        WireFrame->setGeometry(QRect(260, 20, 77, 31));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        WireFrame->setPalette(palette);
        Laplacian = new QPushButton(maillage);
        Laplacian->setObjectName("Laplacian");
        Laplacian->setGeometry(QRect(130, 60, 101, 31));
        Param_L = new QGroupBox(maillage);
        Param_L->setObjectName("Param_L");
        Param_L->setGeometry(QRect(130, 100, 131, 80));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        Param_L->setPalette(palette1);
        Position = new QRadioButton(Param_L);
        Position->setObjectName("Position");
        Position->setGeometry(QRect(10, 30, 91, 22));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        Position->setPalette(palette2);
        Courbure = new QRadioButton(Param_L);
        Courbure->setObjectName("Courbure");
        Courbure->setGeometry(QRect(10, 50, 91, 22));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        Courbure->setPalette(palette3);

        horizontalLayout->addWidget(maillage);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName("mainToolBar");
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Mesh_Computational_Geometry", nullptr));
        Maillage->setText(QCoreApplication::translate("MainWindow", "Maillage", nullptr));
        Import_Mesh->setText(QCoreApplication::translate("MainWindow", "Importer un mesh", nullptr));
        Save_Mesh->setText(QCoreApplication::translate("MainWindow", "Sauver un mesh", nullptr));
        Color->setText(QCoreApplication::translate("MainWindow", "Couleur", nullptr));
        Quit->setText(QCoreApplication::translate("MainWindow", "Quitter", nullptr));
        WireFrame->setText(QCoreApplication::translate("MainWindow", "Wireframe", nullptr));
        Laplacian->setText(QCoreApplication::translate("MainWindow", "Laplacien", nullptr));
        Param_L->setTitle(QCoreApplication::translate("MainWindow", "Param\303\250tres Laplacien", nullptr));
        Position->setText(QCoreApplication::translate("MainWindow", "Position", nullptr));
        Courbure->setText(QCoreApplication::translate("MainWindow", "Courbure", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
