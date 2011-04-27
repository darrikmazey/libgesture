
#ifndef DARMA_FACE_DETECTOR_H
#define DARMA_FACE_DETECTOR_H

#include <opencv.hpp>
#include "facelist.h"
#include "greyscaleimage.h"

class FaceDetector
{
	public:
		FaceDetector();
		~FaceDetector();

		FaceList *detect(GreyscaleImage &image);
		FaceList *detect(GreyscaleImage &image, Face *best);

	protected:
		cv::CascadeClassifier *m_cascade;
};

#endif // DARMA_FACE_DETECTOR_H
