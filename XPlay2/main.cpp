#include "XPlay2.h"
#include <QtWidgets/QApplication>
#include <iostream>
using namespace std;
#include "XDemux.h"
#include "XDecode.h"
#include<QThread>



class TestThread :public QThread
{
public:
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
        cout << "demux.Seek(0.95) = " << demux.Seek(0.95) << endl;


       
        cout << "vdecode.Open(demux.CopyVPara() = " << vdecode.Open(demux.CopyVPara()) << endl;
        /*  vdecode.Clear();
          vdecode.Close();*/
     
        cout << "adecode.Open(demux.CopyAPara() = " << adecode.Open(demux.CopyAPara()) << endl;


        cout << "=============================================" << endl;


    }

    void run()
    {

        while (1)
        {
            AVPacket* pkt = demux.Read();

            if (demux.IsAudio(pkt))
            {
             /*   adecode.Send(pkt);
                AVFrame* frame = adecode.Recv();*/
              
                //cout << "Audio:" << frame << endl;
            }
            else
            {
                vdecode.Send(pkt);
                AVFrame* frame = vdecode.Recv();
                video->Repaint(frame);
                msleep(40);
                //   cout << "Video:" << frame << endl;
            }


            if (pkt == NULL) { cout << endl << "=================================";  break; }
        }


    }
    XDemux demux;
    XDecode vdecode;
    XDecode adecode;
    XVideoWidget* video;

};


bool XDemux::isFirst = true;
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    TestThread tt;
    tt.Init();
    XPlay2 w;
    w.show();
    w.ui.video->Init(tt.demux.width, tt.demux.height);
    tt.video = w.ui.video;
    tt.start();

    return a.exec();
}
