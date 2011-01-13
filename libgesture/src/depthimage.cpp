
#include "depthimage.h"
#include <iostream>

DepthImage::DepthImage() :
	LGImage()
{
	m_pdFilled = false;
}

DepthImage::DepthImage(cv::Mat &mat) :
	LGImage(mat)
{
	m_pdFilled = false;
	fillPD();
}

DepthImage::~DepthImage()
{
	delete(m_pdMat);
}

DepthImage DepthImage::convert(int type, double alpha, double beta)
{
	cv::Mat newMat(m_mat->size(), type);
	m_mat->convertTo(newMat, type, alpha, beta);
	return(DepthImage(newMat));
}

DepthImage DepthImage::greyscaleHeatMap()
{
	return(convert(CV_8UC1, 255.0/2048.0));
}

void DepthImage::fillPD()
{
	if (!m_pdFilled) {
		m_pdMat = new cv::Mat_<cv::Vec2b>(m_mat->size().height, m_mat->size().width, cv::Vec2b(35,0));
		for (int y = 0; y < 480; y++) {
			for (int x = 0; x < 640; x++) {
				(*m_pdMat)(y,x) = cv::Vec2b(planeAt(x,y), depthAt(x,y));
			}
		}
		m_pdFilled = true;
	}
}

void DepthImage::filter(int p, int d)
{
	for (int y = 0; y < 480; y++) {
		for (int x = 0; x < 640; x++) {
			if (planeAt(x,y) > p || (planeAt(x,y) == p && depthAt(x,y) > d)) {
				(*m_pdMat)(y,x) = cv::Vec2b(35,0);
			}
		}
	}
}

RGBImage DepthImage::heatMap()
{
	cv::Mat_<cv::Vec3b> newMat(m_pdMat->size().height, m_pdMat->size().width, cv::Vec3b(0,0,0));
	for (int y = 0; y < 480; y++) {
		for (int x = 0; x < 640; x++) {
			int p = planeAt(x, y);
			int d = depthAt(x, y);
			switch(p) {
				case 0:
					newMat(y,x) = cv::Vec3b(255-d, 255-d, 255);
					break;
				case 1:
					newMat(y,x) = cv::Vec3b(0,d,255);
					break;
				case 2:
					newMat(y,x) = cv::Vec3b(0,255,255-d);
					break;
				case 3:
					newMat(y,x) = cv::Vec3b(d, 255, 0);
					break;
				case 4:
					newMat(y,x) = cv::Vec3b(255, 255-d, 0);
					break;
				case 5:
					newMat(y,x) = cv::Vec3b(255-d, 0, 0);
					break;
				default:
					newMat(y,x) = cv::Vec3b(0,0,0);
					break;
			}
		}
	}
	return(RGBImage(newMat));
}

int DepthImage::depthAt(int x, int y)
{
	if (m_pdFilled) {
		return((*m_pdMat)(y,x)[1]);
	} else {
		int n = (*cvMat()).at<uint16_t>(y, x);
		return(m_gamma[n] % 256);
	}
}

int DepthImage::planeAt(int x, int y)
{
	if (m_pdFilled) {
		return((*m_pdMat)(y,x)[0]);
	} else {
		int n = (*cvMat()).at<uint16_t>(y, x);
		return(m_gamma[n] >> 8);
	}
}

