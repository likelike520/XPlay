#include "XVideoThread.h"
#include "XDecode.h"
#include <iostream>
using namespace std;

bool XVideoThread::Open(AVCodecParameters* para, IVideoCall* call,int width, int height)
{
	if (!para) return false;

	Clear();


	vmux.lock();
	synpts = 0;
	if (call)
	{
		this->call = call;
		call->Init(width, height);
	}
	vmux.unlock();
	bool re = true;

	if (!decode->Open(para))
	{
		cout << "video decode->Open failed!" << endl;
		re = false;
	}
	
	cout << "XVideoThread::Open:" << re << endl;
	return re;
}



void XVideoThread::run()
{
	while (!isExit)
	{
		vmux.lock();
		if (this->isPause)
		{
			vmux.unlock();
			msleep(5);
			continue;
		}

		/*if (packs.empty() || !decode)
		{
			vmux.unlock();
			msleep(1);
			continue;
		}*/


		if (synpts > 0 &&synpts < decode->pts)
		{
			vmux.unlock();
			msleep(1);
			continue;
		}

	/*	AVPacket* pkt = packs.front();
		packs.pop_front();
		decode->Send(pkt);*/

		AVPacket* pkt = Pop();
		int re = decode->Send(pkt);
		if (!re)
		{
			vmux.unlock();
			msleep(1);
			continue;
		}


		while (!isExit)
		{
			AVFrame* frame = decode->Recv();
			if (!frame) break;
			if (call)
			{
				call->Repaint(frame);
			}

		}
		vmux.unlock();

	}
	
}

XVideoThread::XVideoThread()
{
}

XVideoThread::~XVideoThread()
{
	
}

void XVideoThread::SetPause(bool isPause)
{
	vmux.lock();
	this->isPause = isPause;
	vmux.unlock();
}
