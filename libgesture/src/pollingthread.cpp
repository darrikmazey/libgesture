
#include "pollingthread.h"
#include <opencv.hpp>
#include <iostream>
#include "libgesture.h"

PollingThread::PollingThread() :
	m_stop(false)
{
}

PollingThread::~PollingThread()
{
}

bool PollingThread::start()
{
	m_stop = false;
	if (pthread_create(&m_thread, NULL, start_thread, (void*)this) != 0) {
		return(false);
	}
	return(true);
}

bool PollingThread::stop()
{
	m_stop = true;
	pthread_join(m_thread, NULL);
	return(true);
}

void *PollingThread::start_thread(void *data)
{
	PollingThread *pt = static_cast<PollingThread*>(data);
	pt->threadfunc();
}

void PollingThread::threadfunc()
{
	while(!m_stop) {
		//std::cout << "polling" << std::endl;
		GestureContext *ctx = LibGesture::context();
		if (ctx) {
			//std::cout << "have context" << std::endl;
			cv::Mat3b rgbMat(640,480, cv::Vec3b(0,0,0));
			cv::Mat_<uint16_t> depthMat(640,480, (uint16_t)0);
			if (ctx->device()->getVideo(rgbMat)) {
				RGBImage *rgb_image = new RGBImage(rgbMat);
				ctx->newRGBImage(rgb_image);
			}
			if (ctx->device()->getDepth(depthMat)) {
				DepthImage *depth_image = new DepthImage(depthMat);
				ctx->newDepthImage(depth_image);
			}
		} else {
			//std::cout << "no context" << std::endl;
		}
	}
}
