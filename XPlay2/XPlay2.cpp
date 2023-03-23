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

    startTimer(40);
}



void XPlay2::OpenFile()
{
    /*qDebug() << "111111111110";*/
    QString name = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择视频文件"));
    if (name.isEmpty())
    {
        return;
    }

    SetPause(false);
    dt.SetPause(false);
    this->setWindowTitle(name);
    if (!dt.Open(name.toLocal8Bit(), ui.video))
    {
        QMessageBox::information(0, "error", "open file failed!");
        return;
    }
   
}

XPlay2::~XPlay2()
{
    dt.Close();
}



void XPlay2::timerEvent(QTimerEvent* s)
{
    long long total = dt.totalMs;
    if (total > 0)
    {
        double pos = (double)dt.pts / (double)total;

        int v = ui.playPos->maximum() * pos;
        ui.playPos->setValue(v);

    }

}





void XPlay2::resizeEvent(QResizeEvent* s)
{
    ui.playPos->move(50, this->height() - 100);
    ui.playPos->resize(this->width() - 100, ui.playPos->height());
    ui.openFile->move(100, this->height() - 150);
    ui.isPlay->move(ui.openFile->x() + ui.openFile->width() + 10, ui.openFile->y());
    ui.video->resize(this->size());

}

void XPlay2::mouseDoubleClickEvent(QMouseEvent* s)
{
    if (isFullScreen())
    {
        this->showNormal();
    }
    else
    {
        this->showFullScreen();
    }


}

void XPlay2::SetPause(bool isPause)
{
    if (isPause)
    {
        ui.isPlay->setText("播 放");
    }
    else
    {
        ui.isPlay->setText("暂 停");
    }
}

void XPlay2::PlayOrPause()
{
    bool isPause = !dt.isPause;
    SetPause(isPause);
    dt.SetPause(isPause);
}
