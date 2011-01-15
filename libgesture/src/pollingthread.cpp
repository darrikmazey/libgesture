
#include "pollingthread.h"
#include <opencv.hpp>
#include <iostream>
#include "libgesture.h"

PollingThread::PollingThread() :
	m_stop(false), m_last_rgb_image(0), m_last_depth_image(0)
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
			RGBImage *old_rgb_image = m_last_rgb_image;
			DepthImage *old_depth_image = m_last_depth_image;
			cv::Mat_<cv::Vec3b> rgbMat(640,480, cv::Vec3b(0,0,0));
			cv::Mat_<uint16_t> depthMat(640,480, (uint16_t)0);
			ctx->device()->getVideo(rgbMat);
			m_last_rgb_image = new RGBImage(rgbMat);
			ctx->device()->getDepth(depthMat);
			m_last_depth_image = new DepthImage(depthMat);
			if (old_rgb_image) {
				delete(old_rgb_image);
				old_rgb_image = 0;
			}
			if (old_depth_image) {
				delete(old_depth_image);
				old_depth_image = 0;
			}
			std::cout << "depth at (320,240): " << m_last_depth_image->depthAt(320,240) << std::endl;
		} else {
			//std::cout << "no context" << std::endl;
		}
	}
}
