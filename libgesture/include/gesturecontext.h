
#ifndef DARMA_GESTURE_CONTEXT_H
#define DARMA_GESTURE_CONTEXT_H

#include <libfreenect.hpp>
#include "lgfreenectdevice.h"
#include "pollingthread.h"

class GestureContext
{
	public:
		GestureContext();
		~GestureContext();

		LGFreenectDevice *device() const;
	
	private:
		Freenect::Freenect *m_freenect;
		LGFreenectDevice *m_device;
		PollingThread *m_polling_thread;
};

#endif // DARMA_GESTURE_CONTEXT_H
