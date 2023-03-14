#pragma once
#include<stdio.h>
#include<mutex>
struct AVFormatContext;
struct AVPacket;
struct AVCodecParameters;


class XDemux
{
public:
	virtual bool Open(const char* url);
	virtual AVPacket* Read();

	virtual bool IsAudio(AVPacket* pkt);

	virtual AVCodecParameters* CopyVPara();
	
	virtual AVCodecParameters* CopyAPara();


	virtual bool Seek(double pos);

	virtual void Clear();
	virtual void Close();
	XDemux();
	virtual ~XDemux();

	int totalMs = 0;
	int width = 0;
	int height = 0;
	int sampleRate = 0;
	int channels = 0;

protected:
	AVFormatContext* ic = NULL;
	int videoStream = -1;
	int audioStream = -1;
	static bool isFirst;
	std::mutex mux;
};

