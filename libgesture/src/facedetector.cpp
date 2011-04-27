
#include "facedetector.h"
#include <iostream>

FaceDetector::FaceDetector()
{
	m_cascade = new cv::CascadeClassifier("../haarcascade_frontalface_alt.xml");
}

FaceDetector::~FaceDetector()
{
	if (m_cascade) {
		delete(m_cascade);
		m_cascade = 0;
	}
}

FaceList *FaceDetector::detect(GreyscaleImage &image)
{
	std::cout << "FaceDetector::detect(image)" << std::endl;
	cv::imshow("fdgrey", *(image.cvMat()));
	FaceList *fl = new FaceList();
	std::vector<cv::Rect> rects;
	m_cascade->detectMultiScale((*(image.cvMat())), rects);
	for (int i = 0; i < rects.size(); i++) {
		cv::Rect nr = rects[i];
		Face *f = new Face(nr);
		fl->insert(f);
	}
	return(fl);
}

FaceList *FaceDetector::detect(GreyscaleImage &image, Face *face)
{
	if (!face) {
		std::cout << "no face" << std::endl;
		return(detect(image));
	}
	std::cout << "FaceDetector::detect(image, face (" << face->center().x << ", " << face->center().y << "))" << std::endl;
	cv::Mat1b newMat(image.cvMat()->clone(), image.clipRect(face->detectionRect()));
	GreyscaleImage crop(newMat);
	cv::imshow("crop", *(crop.cvMat()));
	return(new FaceList());
	FaceList *faces = detect(crop);
	std::cout << "detected " << faces->size() << " faces" << std::endl;
	return(faces);
}
