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

    void run();
    virtual ~XDemuxThread(); 
    XDemuxThread();
    bool isExit = false;

protected:
    XAudioThread* at = 0;
    XVideoThread* vt = 0;
    XDemux* demux = 0;
    std::mutex mux;
    
};

