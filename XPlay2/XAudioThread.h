#pragma once

class XResample;
class XAudioPlay;

#include "XDecodeThread.h"

class XAudioThread:public XDecodeThread
{
public:
	long long pts = 0;

	virtual bool Open(AVCodecParameters* para, int sampleRate, int channels);

	virtual void Close();

	void run();

	int maxList = 100;
	bool isEixt = false;

	void SetPause(bool isPause);
	bool isPause = false;

	XAudioThread();
	virtual ~XAudioThread();

protected:

	std::mutex amux;
	XResample *res = 0;
	XAudioPlay* ap = 0;
};

