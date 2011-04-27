
#ifndef DARMA_GESTURE_CONTEXT_H
#define DARMA_GESTURE_CONTEXT_H

#include <libfreenect.hpp>
#include "lgfreenectdevice.h"
#include "pollingthread.h"
#include "mutex.h"
#include "facelist.h"
#include "facedetector.h"

class GestureContext
{
	public:
		GestureContext();
		~GestureContext();

		LGFreenectDevice *device() const;
	
		RGBImage *lastRGBImage();
		DepthImage *lastDepthImage();

		void newRGBImage(RGBImage *image);
		void newDepthImage(DepthImage *image);

		Face *face();

		RGBImage drawSkeleton();

	private:
		void postProcessRGB();
		void postProcessDepth();

		Freenect::Freenect *m_freenect;
		LGFreenectDevice *m_device;
		PollingThread *m_polling_thread;
		Mutex m_rgb_mutex;
		Mutex m_depth_mutex;
		RGBImage *m_last_rgb_image;
		DepthImage *m_last_depth_image;
		volatile bool m_new_rgb_image;
		volatile bool m_new_depth_image;

		FaceList *m_face_list;
		FaceDetector *m_face_detector;
};

#endif // DARMA_GESTURE_CONTEXT_H
