/********************************************************************************
** Form generated from reading UI file 'XPlay2.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XPLAY2_H
#define UI_XPLAY2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <xslider.h>
#include "XVideoWidget.h"

QT_BEGIN_NAMESPACE

class Ui_XPlay2Class
{
public:
    XVideoWidget *video;
    QPushButton *openFile;
    XSlider *playPos;
    QPushButton *isPlay;

    void setupUi(QWidget *XPlay2Class)
    {
        if (XPlay2Class->objectName().isEmpty())
            XPlay2Class->setObjectName(QString::fromUtf8("XPlay2Class"));
        XPlay2Class->resize(1280, 720);
        video = new XVideoWidget(XPlay2Class);
        video->setObjectName(QString::fromUtf8("video"));
        video->setGeometry(QRect(0, 0, 1280, 720));
        openFile = new QPushButton(XPlay2Class);
        openFile->setObjectName(QString::fromUtf8("openFile"));
        openFile->setGeometry(QRect(590, 620, 91, 41));
        openFile->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 255, 0);"));
        playPos = new XSlider(XPlay2Class);
        playPos->setObjectName(QString::fromUtf8("playPos"));
        playPos->setGeometry(QRect(30, 680, 1221, 22));
        playPos->setMaximum(999);
        playPos->setOrientation(Qt::Horizontal);
        isPlay = new QPushButton(XPlay2Class);
        isPlay->setObjectName(QString::fromUtf8("isPlay"));
        isPlay->setGeometry(QRect(720, 620, 81, 41));

        retranslateUi(XPlay2Class);
        QObject::connect(openFile, SIGNAL(clicked()), XPlay2Class, SLOT(OpenFile()));
        QObject::connect(isPlay, SIGNAL(clicked()), XPlay2Class, SLOT(PlayOrPause()));
        QObject::connect(playPos, SIGNAL(sliderPressed()), XPlay2Class, SLOT(SliderPress()));
        QObject::connect(playPos, SIGNAL(sliderReleased()), XPlay2Class, SLOT(SliderRelease()));

        QMetaObject::connectSlotsByName(XPlay2Class);
    } // setupUi

    void retranslateUi(QWidget *XPlay2Class)
    {
        XPlay2Class->setWindowTitle(QApplication::translate("XPlay2Class", "XPlay2", nullptr));
        openFile->setText(QApplication::translate("XPlay2Class", "\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
        isPlay->setText(QApplication::translate("XPlay2Class", "\346\222\255 \346\224\276", nullptr));
    } // retranslateUi

};

namespace Ui {
    class XPlay2Class: public Ui_XPlay2Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XPLAY2_H
