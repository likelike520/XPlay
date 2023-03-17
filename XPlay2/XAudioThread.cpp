#include "XAudioThread.h"
#include"XDecode.h"
#include"XResample.h"
#include"XAudioPlay.h"
#include<iostream>
using namespace std;

bool XAudioThread::Open(AVCodecParameters* para, int sampleRate, int channels)
{
	if (!para) return false;
	mux.lock();
	if (!decode) decode = new XDecode();
	if (!res) res = new XResample();
	if (!ap) ap = XAudioPlay::Get();

	bool re = true;
	if (!res->Open(para))
	{
		cout << "res->Open(para) failed!" << endl;
		re = false;
	}

	if (!decode->Open(para))
	{
		cout << "decode->Open(para) failed!" << endl;
		re = false;
	}

	ap->sampleRate = sampleRate;
	ap->channels = channels;
	if (!ap->Open())
	{
		cout << "ap->Open() failed!" << endl;
		re = false;
	}

	mux.unlock();

	cout << "XAudioThread::Open :" << re << endl;
	return re;
}

void XAudioThread::Push(AVPacket* pkt)
{
	if (!pkt) return;
	while (!isEixt)
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

void XAudioThread::run()
{
	unsigned char* pcm = new unsigned char[1024 * 1024 * 10];

	while (!isEixt)
	{
		mux.lock();

		if (packs.empty() || !decode || !res || !ap)
		{
			mux.unlock();
			msleep(1);
			continue;
		}
		AVPacket* pkt = packs.front();
		packs.pop_front();
		bool re = decode->Send(pkt);
		if (!re)
		{
			mux.unlock();
			msleep(1);
			continue;
		}


		while (!isEixt)
		{
			AVFrame* frame = decode->Recv();
			if (!frame) break;

			int size = res->Resample(frame, pcm);

			while (!isEixt)
			{
				if (size <= 0) break;

				if (ap->GetFree() < size)
				{
					msleep(1);
					continue;
				}

				ap->Write(pcm, size);
				break;
			}

		}



		mux.unlock();

	}


	delete pcm;

}

XAudioThread::~XAudioThread()
{
	isEixt = true;
	wait();
}
