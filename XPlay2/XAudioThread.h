#pragma once
#include <QThread>
#include<list>
#include<mutex>
struct AVCodecParameters;
struct AVPacket;
class XDecode;
class XResample;
class XAudioPlay;


class XAudioThread:public QThread
{
public:
	virtual bool Open(AVCodecParameters* para, int sampleRate, int channels);
	virtual void Push(AVPacket* pkt);
	void run();

	int maxList = 100;
	bool isEixt = false;
	~XAudioThread();
protected:

	std::list<AVPacket*> packs;
	std::mutex mux;
	XDecode *decode = 0;
	XResample *res = 0;
	XAudioPlay* ap = 0;
};

