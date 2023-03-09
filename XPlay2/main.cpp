#include "XPlay2.h"
#include <QtWidgets/QApplication>
#include <iostream>
using namespace std;
#include "XDemux.h"
#include "XDecode.h"
bool XDemux::isFirst = true;
int main(int argc, char *argv[])
{

    char* url = "v1080.mp4";
    XDemux demux;

    cout << "demux.open = " << demux.Open(url) << endl;

    demux.Read();
    demux.Clear();
    demux.Close();


    cout << "demux.open = " << demux.Open(url) << endl;
    cout << "demux.CopyVPara = " << demux.CopyVPara() << endl;
    cout << "demux.CopyAPara = " << demux.CopyAPara() << endl;
    cout << "demux.Seek(0.95) = " << demux.Seek(0.95) << endl;


    XDecode vdecode;
    cout << "vdecode.Open(demux.CopyVPara() = " << vdecode.Open(demux.CopyVPara()) << endl;
  /*  vdecode.Clear();
    vdecode.Close();*/
    XDecode adecode;
    cout << "adecode.Open(demux.CopyAPara() = " << adecode.Open(demux.CopyAPara()) << endl;


    cout << "=============================================" << endl;
    while (1)
    {
        AVPacket* pkt = demux.Read();

        if (demux.IsAudio(pkt)) 
        {
            adecode.Send(pkt);
            AVFrame* frame = adecode.Recv();
            //cout << "Audio:" << frame << endl;
        }
        else
        {
            vdecode.Send(pkt);
            AVFrame* frame = vdecode.Recv();
         //   cout << "Video:" << frame << endl;
        }


        if (pkt == NULL) { cout << endl <<"=================================";  break;}
    }



    QApplication a(argc, argv);
    XPlay2 w;
    w.show();
    return a.exec();
}
