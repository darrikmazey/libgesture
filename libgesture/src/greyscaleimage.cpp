
#include "greyscaleimage.h"
#include <iostream>

GreyscaleImage::GreyscaleImage()
{
	m_mat = 0;
	setupGamma();
}

GreyscaleImage::GreyscaleImage(cv::Mat_<uint8_t> &mat)
{
	m_mat = new cv::Mat_<uint8_t>(mat);
	mat.copyTo(*m_mat);
	setupGamma();
}

GreyscaleImage::~GreyscaleImage()
{
	delete(m_mat);
}

cv::Mat_<uint8_t> *GreyscaleImage::cvMat()
{
	return(m_mat);
}

void GreyscaleImage::setupGamma()
{
	for (int i = 0; i < 2048; i++)
	{
		float v = i/2048.0;
		v = powf(v, 3) * 6;
		m_gamma[i] = v * 6 * 256;
	}
}

//GreyscaleImage GreyscaleImage::greyscale()
//{
//	cv::Mat_< cv::Vec<uchar, 1> > grey(cvMat()->size(), cv::Vec<uchar, 1>(0));
//	IplImage iplGrey(grey);
//	IplImage iplThis(*(cvMat()));
//	cvCvtColor(&iplThis, &iplGrey, CV_BGR2GRAY);
//	return(GreyscaleImage(grey));
//}
//
//void GreyscaleImage::mask(GreyscaleImage &mask)
//{
//	for (int y = 0; y < 480; y++) {
//		for (int x = 0; x < 640; x++) {
//			if ((*(mask.cvMat()))(y,x) == cv::Vec3b(0,0,0)) {
//				(*(cvMat()))(y,x) = cv::Vec3b(0,0,0);
//			}
//		}
//	}
//}
//
