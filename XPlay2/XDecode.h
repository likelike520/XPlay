#pragma once

struct AVCodecParameters;
struct AVCodecContext;
struct AVFrame;
struct AVPacket;
#include<mutex>
class XDecode
{

public:
	bool isAudio = false;

	virtual bool Open(AVCodecParameters *para);

	virtual bool Send(AVPacket* pkt);
	virtual AVFrame* Recv();


	virtual void Close();
	virtual void Clear();

	XDecode();
	virtual~XDecode();


protected:
	AVCodecContext* codec = 0;
	std::mutex mux;
};

