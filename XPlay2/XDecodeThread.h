#pragma once
#include <QThread>
#include<list>
#include<mutex>
struct AVCodecParameters;
struct AVPacket;
class XDecode;
class XDecodeThread : public QThread
{
public:
    XDecodeThread();
    virtual ~XDecodeThread();

    virtual void Push(AVPacket* pkt);

  

    virtual void Clear();

    virtual void Close();

    virtual AVPacket* Pop();

    int maxList = 100;
    bool isExit = false;


protected:
    std::list<AVPacket*> packs;
    std::mutex mux;
    XDecode* decode = 0;

};

