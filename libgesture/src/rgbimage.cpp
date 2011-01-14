
#include "rgbimage.h"
#include "greyscaleimage.h"
#include <iostream>

RGBImage::RGBImage()
{
	m_mat = 0;
	setupGamma();
}

RGBImage::RGBImage(cv::Mat_<cv::Vec3b> &mat)
{
	m_mat = new cv::Mat_<cv::Vec3b>(mat);
	mat.copyTo(*m_mat);
	setupGamma();
}

RGBImage::~RGBImage()
{
	delete(m_mat);
}

cv::Mat_<cv::Vec3b> *RGBImage::cvMat()
{
	return(m_mat);
}

void RGBImage::setupGamma()
{
	for (int i = 0; i < 2048; i++)
	{
		float v = i/2048.0;
		v = powf(v, 3) * 6;
		m_gamma[i] = v * 6 * 256;
	}
}

GreyscaleImage RGBImage::greyscale()
{
	cv::Mat_<uint8_t> grey(cvMat()->size(), 0);
	IplImage iplGrey(grey);
	IplImage iplThis(*(cvMat()));
	cvCvtColor(&iplThis, &iplGrey, CV_BGR2GRAY);
	return(GreyscaleImage(grey));
}

void RGBImage::drawCrosshairs(int x, int y, cv::Scalar &color, int thickness, int lineType, int shift)
{
	line(*m_mat, cv::Point(x-5, y), cv::Point(x+5, y), color, thickness, lineType, shift);
	line(*m_mat, cv::Point(x, y-5), cv::Point(x, y+5), color, thickness, lineType, shift);
}

//void RGBImage::mask(RGBImage &mask)
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
