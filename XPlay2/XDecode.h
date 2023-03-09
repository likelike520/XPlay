#pragma once

struct AVCodecParameters;
struct AVCodecContext;
#include<mutex>
class XDecode
{

public:
	bool isAudio = false;

	virtual bool Open(AVCodecParameters *para);

	virtual void Close();
	virtual void Clear();

	XDecode();
	virtual~XDecode();


protected:
	AVCodecContext* codec = 0;
	std::mutex mux;
};

