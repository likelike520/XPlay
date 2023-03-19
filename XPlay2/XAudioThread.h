#pragma once
#include <QThread>
#include<list>
#include<mutex>
struct AVCodecParameters;
struct AVPacket;
class XDecode;
class XResample;
class XAudioPlay;

#include "XDecodeThread.h"

class XAudioThread:public XDecodeThread
{
public:
	long long pts = 0;

	virtual bool Open(AVCodecParameters* para, int sampleRate, int channels);
	void run();

	int maxList = 100;
	bool isEixt = false;
	XAudioThread();
	virtual ~XAudioThread();

protected:

	std::mutex amux;
	XResample *res = 0;
	XAudioPlay* ap = 0;
};

