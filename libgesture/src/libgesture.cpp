
#include "libgesture.h"

GestureContext *LibGesture::init()
{
	if (!s_context) {
		s_context = new GestureContext();
	}
	return(s_context);
}

GestureContext *LibGesture::context()
{
	return(s_context);
}

GestureContext *LibGesture::s_context = 0;
