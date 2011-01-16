
#include "gesturecontext.h"
#include <iostream>

GestureContext::GestureContext() :
	m_last_rgb_image(0), m_last_depth_image(0), m_new_rgb_image(false), m_new_depth_image(false)
{
	std::cout << "GestureContext::GestureContext()" << std::endl;
	m_freenect = new Freenect::Freenect();
	m_device = &m_freenect->createDevice<LGFreenectDevice>(0);
	m_device->startVideo();
	m_device->startDepth();
	m_polling_thread = new PollingThread();
	m_polling_thread->start();
}

GestureContext::~GestureContext()
{
	std::cout << "GestureContext::~GestureContext()" << std::endl;
	m_polling_thread->stop();
	m_device->stopDepth();
	m_device->stopVideo();
	m_device = 0;
	delete(m_freenect);
	if (m_last_rgb_image) {
		delete(m_last_rgb_image);
		m_last_rgb_image = 0;
	}
	if (m_last_depth_image) {
		delete(m_last_depth_image);
		m_last_depth_image = 0;
	}
}

LGFreenectDevice *GestureContext::device() const
{
	return(m_device);
}

RGBImage *GestureContext::lastRGBImage()
{
	m_rgb_mutex.lock();
	if (!m_new_rgb_image) {
		m_rgb_mutex.unlock();
		return(0);
	}
	if (!m_last_rgb_image) {
		m_rgb_mutex.unlock();
		return(0);
	}
	RGBImage *img = new RGBImage(*m_last_rgb_image);
	m_new_rgb_image = false;
	m_rgb_mutex.unlock();
	return(img);
}

DepthImage *GestureContext::lastDepthImage()
{
	m_depth_mutex.lock();
	if (!m_new_depth_image) {
		m_depth_mutex.unlock();
		return(0);
	}
	if (!m_last_depth_image) {
		m_depth_mutex.unlock();
		return(0);
	}
	DepthImage *img = new DepthImage(*m_last_depth_image);
	m_new_depth_image = false;
	m_depth_mutex.unlock();
	return(img);
}

void GestureContext::newRGBImage(RGBImage *image)
{
	m_rgb_mutex.lock();
	if (m_last_rgb_image) {
		delete(m_last_rgb_image);
		m_last_rgb_image = 0;
	}
	m_last_rgb_image = new RGBImage(*image);
	m_new_rgb_image = true;
	m_rgb_mutex.unlock();
}

void GestureContext::newDepthImage(DepthImage *image)
{
	m_depth_mutex.lock();
	if (m_last_depth_image) {
		delete(m_last_depth_image);
		m_last_depth_image = 0;
	}
	m_last_depth_image = new DepthImage(*image);
	m_new_depth_image = true;
	m_depth_mutex.unlock();
}

