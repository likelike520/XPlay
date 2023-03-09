#include "XDecode.h"
extern "C"
{
#include"libavcodec/avcodec.h"
}
#include<iostream>
using namespace std;

bool XDecode::Open(AVCodecParameters* para)
{
	if (!para) return false;
	Close();
	const AVCodec*vcodec = avcodec_find_decoder(para->codec_id);
	if (!vcodec)
	{
		char buf[1024] = { 0 };
		avcodec_parameters_free(&para);
		cout << "can't find AVCodec" << para->codec_id << endl;
		return false;
	}

	mux.lock();
	codec = avcodec_alloc_context3(vcodec);
	avcodec_parameters_to_context(codec, para);
	avcodec_parameters_free(&para);

	codec->thread_count = 8;

	int re = avcodec_open2(codec, 0, 0);
	if (re != 0)
	{
		char buf[1024] = { 0 };
		avcodec_free_context(&codec);
		mux.unlock();
		av_strerror(re, buf, sizeof(buf) - 1);
		cout << "avcodec_open2 failed!:" << buf << endl;
		return false;
	}
	mux.unlock();
	cout << "avcodec_open2 success!" << endl;
	return true;
}

 void XDecode::Close()
 {
	 mux.lock();

	 if (codec) {
		 avcodec_close(codec);
		 avcodec_free_context(&codec);
	 }

	 mux.unlock();

 }
 void XDecode::Clear()
 {
	 mux.lock();
	 if (codec)
		 avcodec_flush_buffers(codec);

	 mux.unlock();

 }

XDecode::XDecode()
{
	

}
XDecode::~XDecode()
{

}