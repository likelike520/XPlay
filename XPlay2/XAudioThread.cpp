#include "XAudioThread.h"
#include"XDecode.h"
#include"XResample.h"
#include"XAudioPlay.h"
#include<iostream>
using namespace std;

bool XAudioThread::Open(AVCodecParameters* para, int sampleRate, int channels)
{
	if (!para) return false;
	amux.lock();
	pts = 0;


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

	amux.unlock();

	cout << "XAudioThread::Open :" << re << endl;
	return re;
}



void XAudioThread::run()
{
	unsigned char* pcm = new unsigned char[1024 * 1024 * 10];

	while (!isEixt)
	{
		amux.lock();

		if (packs.empty() || !decode || !res || !ap)
		{
			amux.unlock();
			msleep(1);
			continue;
		}
		AVPacket* pkt = packs.front();
		packs.pop_front();
		bool re = decode->Send(pkt);
		if (!re)
		{
			amux.unlock();
			msleep(1);
			continue;
		}


		while (!isEixt)
		{
			AVFrame* frame = decode->Recv();
			if (!frame) break;

			//减去缓冲中没播放的时间
			pts = decode->pts - ap->GetNoPlayMs();
			cout << "auido syn :" << pts<<endl;

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



		amux.unlock();

	}


	delete pcm;

}

XAudioThread::XAudioThread()
{
	if (!res) res = new XResample();
	if (!ap) ap = XAudioPlay::Get();

}

XAudioThread::~XAudioThread()
{
	isEixt = true;
	wait();
}
