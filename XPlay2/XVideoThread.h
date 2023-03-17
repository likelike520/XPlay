#pragma once
#include <QThread>
#include<list>
#include<mutex>
struct AVCodecParameters;
struct AVPacket;
class XDecode;

#include "IVideoCall.h"

class XVideoThread:public QThread
{
public:
	virtual bool Open(AVCodecParameters* para, IVideoCall* call,int width, int height);
	virtual void Push(AVPacket* pkt);
	void run();

	int maxList = 100;
	bool isExit = false;
	~XVideoThread();

protected:
	std::list<AVPacket*> packs;
	std::mutex mux;
	XDecode* decode = 0;
	IVideoCall* call = 0;
};

