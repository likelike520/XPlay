#include "XPlay2.h"
#include <QtWidgets/QApplication>
#include <iostream>
using namespace std;
#include "XDemux.h"
#include "XDecode.h"
#include "XResample.h"
#include<QThread>
#include"XAudioPlay.h"
#include"XAudioThread.h"
#include"XVideoThread.h"

#include"XDemuxThread.h"

class TestThread :public QThread
{
public:
    XAudioThread at;
    XVideoThread vt;
    void Init()
    {

        char* url = "v1080.mp4";
    

        cout << "demux.open = " << demux.Open(url) << endl;

        demux.Read();
        demux.Clear();
        demux.Close();


        cout << "demux.open = " << demux.Open(url) << endl;
        cout << "demux.CopyVPara = " << demux.CopyVPara() << endl;
        cout << "demux.CopyAPara = " << demux.CopyAPara() << endl;
        //cout << "demux.Seek(0.95) = " << demux.Seek(0.95) << endl;


       
       // cout << "vdecode.Open(demux.CopyVPara() = " << vdecode.Open(demux.CopyVPara()) << endl;
        /*  vdecode.Clear();
          vdecode.Close();*/
     
        /*cout << "adecode.Open(demux.CopyAPara() = " << adecode.Open(demux.CopyAPara()) << endl;
        cout << "resample.Open() = " << resample.Open(demux.CopyAPara()) << endl;

        XAudioPlay::Get()->channels = demux.channels;
        XAudioPlay::Get()->sampleRate = demux.sampleRate;

        cout << "XAudioPlay::Get()->Open() = " << XAudioPlay::Get()->Open()<< endl;*/
        cout << "av.Open = " << vt.Open(demux.CopyVPara(), video, demux.width, demux.height);
        cout << "at.Open = " << at.Open(demux.CopyAPara(), demux.sampleRate, demux.channels);
        at.start();
        vt.start();

        cout << "=============================================" << endl;


    }

    unsigned char* pcm = new unsigned char[1024 * 1024];

    void run()
    {

        while (1)
        {
            AVPacket* pkt = demux.Read();

            if (demux.IsAudio(pkt))
            {
              /*adecode.Send(pkt);
                AVFrame* frame = adecode.Recv();
               //cout<<"resample:"<< resample.Resample(frame, pcm)<<endl;
                int len = resample.Resample(frame, pcm);
                cout << "resample:" << len << " ";
                //cout << "Audio:" << frame << endl;
                while (len > 0)
                {
                    if (XAudioPlay::Get()->GetFree() >= len)
                    {
                        XAudioPlay::Get()->Write(pcm, len);
                        break;
                    }
                    msleep(1);
               }*/  
                at.Push(pkt);
            }
            else
            {
               /* vdecode.Send(pkt);
                AVFrame* frame = vdecode.Recv();
                video->Repaint(frame);*/
               // msleep(40);
                //   cout << "Video:" << frame << endl;
                vt.Push(pkt);
            }


            if (pkt == NULL) { cout << endl << "=================================";  break; }
        }


    }
    XDemux demux;
    XVideoWidget* video = 0;
    //XDecode vdecode;
   /* XDecode adecode;
    XResample resample;*/


};


bool XDemux::isFirst = true;
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    

    XPlay2 w;
    w.show();
    XDemuxThread dt;
    dt.Open("v1080.mp4", w.ui.video);
    dt.Start();

    /*TestThread tt;
    w.ui.video->Init(tt.demux.width, tt.demux.height);
    tt.video = w.ui.video;
    tt.Init();
    tt.start();*/

    return a.exec();
}
