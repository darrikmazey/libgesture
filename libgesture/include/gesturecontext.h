
#ifndef DARMA_GESTURE_CONTEXT_H
#define DARMA_GESTURE_CONTEXT_H

#include "libfreenect.hpp"
#include "lgfreenectdevice.h"

class GestureContext
{
	public:
		GestureContext();
		~GestureContext();
	
	private:
		Freenect::Freenect m_freenect;
		LGFreenectDevice *m_device;
};

#endif // DARMA_GESTURE_CONTEXT_H
