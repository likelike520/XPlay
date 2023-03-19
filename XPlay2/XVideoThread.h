#pragma once


#include "IVideoCall.h"
#include "XDecodeThread.h"

class XVideoThread:public XDecodeThread
{
public:
	virtual bool Open(AVCodecParameters* para, IVideoCall* call,int width, int height);
	void run();

	XVideoThread();

	virtual ~XVideoThread();

	long long synpts = 0;

protected:
	
	std::mutex vmux;
	IVideoCall* call = 0;
};

