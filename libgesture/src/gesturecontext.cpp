
#include "gesturecontext.h"
#include <iostream>

GestureContext::GestureContext()
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
}

LGFreenectDevice *GestureContext::device() const
{
	return(m_device);
}
