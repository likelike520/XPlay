#pragma once

#include <QtWidgets/QWidget>
#include "ui_XPlay2.h"

class XPlay2 : public QWidget
{
    Q_OBJECT

public:
    XPlay2(QWidget *parent = Q_NULLPTR);
    ~XPlay2();

    //定时器 滑动条显示
    void timerEvent(QTimerEvent* s);

    //窗口变化
    void resizeEvent(QResizeEvent* s);


    //双击全屏
    void mouseDoubleClickEvent(QMouseEvent* s);

public slots:
    void OpenFile();

private:
    Ui::XPlay2Class ui;
};
