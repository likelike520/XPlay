#include "XResample.h"
#include<iostream>
using namespace std;
extern "C"
{
#include"libavcodec/avcodec.h"
#include"libswresample/swresample.h"
}

#pragma comment(lib,"swresample.lib")
#pragma comment(lib,"avcodec.lib")
bool XResample::Open(AVCodecParameters* para)
{
    if (!para) return false;
    mux.lock();

    actx = swr_alloc_set_opts(
        actx,
        av_get_default_channel_layout(2),
        AV_SAMPLE_FMT_S16,
        para->sample_rate,
        av_get_default_channel_layout(para->channels),
        (AVSampleFormat)para->format,
        para->sample_rate,
        0, 0
    );

    int re = swr_init(actx);
    mux.unlock();
    if (re != 0)
    {
        char buf[1024] = { 0 };
        av_strerror(re, buf, sizeof(buf) - 1);
        cout << "swr_init  failed! :" << buf << endl;
        return false;
    }

    return true;
}

void  XResample::Close()
{
    mux.lock();
    if (actx)
    {
        swr_free(&actx);
    }
    mux.unlock();

}

int XResample::Resample(AVFrame* indata, unsigned char* d)
{
    if (!indata) return 0;
    if (!d)
    {
        av_frame_free(&indata);
        return 0;
    }

    uint8_t* data[2] = { 0 };
    data[0] = d;
    int re = swr_convert(actx,
        data, indata->nb_samples,		//输出
        (const uint8_t**)indata->data, indata->nb_samples	//输入
    );
    if (re <= 0) return re;
    int outSize = re * indata->channels * av_get_bytes_per_sample((AVSampleFormat)outFormat);
    return outSize;
}

XResample::XResample()
{
}

XResample::~XResample()
{
}
