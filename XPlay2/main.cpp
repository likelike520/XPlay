#include "XPlay2.h"
#include <QtWidgets/QApplication>
#include <iostream>
using namespace std;
#include "XDemux.h"
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

    while (1)
    {
        AVPacket* pkt = demux.Read();
        if (pkt == NULL) { cout << endl <<"=================================";  break;}
    }



    QApplication a(argc, argv);
    XPlay2 w;
    w.show();
    return a.exec();
}
