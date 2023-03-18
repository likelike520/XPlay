#include "XVideoThread.h"
#include "XDecode.h"
#include <iostream>
using namespace std;

bool XVideoThread::Open(AVCodecParameters* para, IVideoCall* call,int width, int height)
{
	if (!para) return false;
	mux.lock();
	synpts = 0;
	if (call)
	{
		this->call = call;
		call->Init(width, height);
	}
	bool re = true;
	decode = new XDecode();
	if (!decode->Open(para))
	{
		cout << "video decode->Open failed!" << endl;
		re = false;
	}
	mux.unlock();
	cout << "XVideoThread::Open:" << re << endl;
	return re;
}

void XVideoThread::Push(AVPacket* pkt)
{
	if (!pkt)return;
	//阻塞
	while (!isExit)
	{
		mux.lock();
		if (packs.size() < maxList)
		{
			packs.push_back(pkt);
			mux.unlock();
			break;
		}
		mux.unlock();
		msleep(1);
	}
}

void XVideoThread::run()
{
	while (!isExit)
	{
		mux.lock();

		if (packs.empty() || !decode)
		{
			mux.unlock();
			msleep(1);
			continue;
		}


		if (synpts < decode->pts)
		{
			mux.unlock();
			msleep(1);
			continue;
		}

		AVPacket* pkt = packs.front();
		packs.pop_front();
		decode->Send(pkt);

		while (!isExit)
		{
			AVFrame* frame = decode->Recv();
			if (!frame) break;
			if (call)
			{
				call->Repaint(frame);
			}

		}
		mux.unlock();

	}
	
}

XVideoThread::~XVideoThread()
{
	isExit = true;
	wait();
}
