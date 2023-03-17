#pragma once
struct AVCodecParameters;
struct AVFrame;
struct SwrContext;
#include<mutex>


class XResample
{
public:
	//输出参数和输入参数一致除采样格式,输出为S16
	virtual bool Open(AVCodecParameters *para ,bool isClearPara = false);
	virtual void Close();

	virtual int Resample(AVFrame* indata, unsigned char* data);
	
	XResample();
	~XResample();


	int outFormat = 1;

protected:
	std::mutex mux;
	SwrContext* actx = 0;
};

