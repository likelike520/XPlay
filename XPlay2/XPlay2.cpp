#include "XPlay2.h"
#include <QFileDialog>
#include"XDemuxThread.h"
#include <QMessageBox>
#include<QDebug>
static XDemuxThread dt;

XPlay2::XPlay2(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    dt.Start();
}



void XPlay2::OpenFile()
{
    qDebug() << "111111111110";
    QString name = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择视频文件"));
    if (name.isEmpty())
    {
        return;
    }

    this->setWindowTitle(name);
    if (!dt.Open(name.toLocal8Bit(), ui.video))
    {
        QMessageBox::information(0, "error", "open file failed!");
        return;
    }

}
