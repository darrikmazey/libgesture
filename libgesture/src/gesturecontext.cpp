
#include "gesturecontext.h"
#include <iostream>

GestureContext::GestureContext()
{
	std::cout << "GestureContext::GestureContext()" << std::endl;
	m_device = &m_freenect.createDevice<LGFreenectDevice>(0);
	m_device->startVideo();
	m_device->startDepth();
}

GestureContext::~GestureContext()
{
	std::cout << "GestureContext::~GestureContext()" << std::endl;
	m_device->stopDepth();
	m_device->stopVideo();
	m_device = 0;
}

