#include "XDemuxThread.h"

#include<iostream>
using namespace std;

bool XDemuxThread::Open(const char* url, IVideoCall* call) 
{
	if (!url || url[0] == '\0') return false;

	mux.lock();


	if (!demux) demux = new XDemux();
	if (!at) at = new XAudioThread();
	if (!vt) vt = new XVideoThread();

	bool re = true;
	if (!demux->Open(url))
	{
		cout << "demux->Open(url) failed!" << endl;
		re = false;
	}
	this->totalMs = demux->totalMs;
	if (!at->Open(demux->CopyAPara(), demux->sampleRate, demux->channels))
	{
		cout << "at->Open failed!" << endl;
		re = false;
	}

	if (!vt->Open(demux->CopyVPara(), call, demux->width, demux->height))
	{
		cout << "vt->Open failed!" << endl;
		re = false;
	}

	cout << "XDemuxThread::Open :" << re << endl;
	mux.unlock();
	return re;

}


 void XDemuxThread::Start()
 {
	 mux.lock();

	 if (!demux) demux = new XDemux();
	 if (!at) at = new XAudioThread();
	 if (!vt) vt = new XVideoThread();

	 QThread::start();
	 if (at) at->start();
	 if (vt) vt->start();
	 
	 mux.unlock();

 }

 void XDemuxThread::Close()
 {
	 isExit = true;
	 wait();

	 if (at) at->Close();
	 if (vt) vt->Close();
	 if (demux) demux->Close();
	 mux.lock();
	 delete vt;
	 delete at;
	 delete demux;
	 vt = NULL;
	 at = NULL;
	 demux = NULL;
	 mux.unlock();

 }

 void XDemuxThread::run()
{
	while (!isExit)
	{
		mux.lock();

		if (isPause)
		{
			mux.unlock();
			msleep(5);
			continue;
		}


		if (!demux)
		{
			mux.unlock();
			msleep(5);
			continue;
		}

		if (at && vt)
		{
			pts = at->pts;
			vt->synpts = at->pts;
		}


		AVPacket* pkt = demux->Read();
		if (!pkt)
		{
			mux.unlock();
			msleep(5);
			continue;
		}

		if (demux->IsAudio(pkt))
		{
			if(at)
				at->Push(pkt);
		}
		else
		{
			if(vt)
				vt->Push(pkt);
		}

		mux.unlock();
		msleep(1);
	}
	
}

XDemuxThread::XDemuxThread()
{

}

void XDemuxThread::SetPause(bool isPause)
{
	mux.lock();
	this->isPause = isPause;
	if (at) at->SetPause(isPause);
	if (vt) vt->SetPause(isPause);
	mux.unlock();


}

XDemuxThread::~XDemuxThread()
{
	isExit = true;
	wait();
}

