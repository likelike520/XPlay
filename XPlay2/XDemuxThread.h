#pragma once
#include <qthread.h>
#include"IVideoCall.h"
#include"XAudioThread.h"
#include"XVideoThread.h"
#include "XDemux.h"

class XDemuxThread :  public QThread
{
public:
    virtual bool Open(const char* url,IVideoCall* call);

    virtual void Start();


    //关闭线程清理资源
    virtual void Close();

    void run();
    virtual ~XDemuxThread(); 
    XDemuxThread();
    bool isExit = false;
    long long totalMs = 0;
    long long pts = 0;

    void SetPause(bool isPause);
    bool isPause = false;

protected:
    XAudioThread* at = 0;
    XVideoThread* vt = 0;
    XDemux* demux = 0;
    std::mutex mux;
    
};

