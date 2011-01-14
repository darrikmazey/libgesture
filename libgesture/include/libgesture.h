
#include "mutex.h"
#include "lgfreenectdevice.h"
#include "gesturecontext.h"
#include "rgbimage.h"
#include "depthimage.h"
#include "greyscaleimage.h"
#include "face.h"
#include "facelist.h"

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
