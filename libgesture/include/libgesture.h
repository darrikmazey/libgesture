
#include "mutex.h"
#include "lgfreenectdevice.h"
#include "gesturecontext.h"

#ifndef DARMA_LIBGESTURE_H
#define DARMA_LIBGESTURE_H

class LibGesture
{
	public:
		static GestureContext *init();
		static GestureContext *context();
	
	private:
		static GestureContext *s_context;
};

#endif // DARMA_LIBGESTURE_H
