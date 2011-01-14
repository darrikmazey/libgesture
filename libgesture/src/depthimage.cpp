
#include "depthimage.h"
#include "rgbimage.h"
#include <iostream>

DepthImage::DepthImage()
{
	m_mat = 0;
	setupGamma();
}

DepthImage::DepthImage(cv::Mat_<cv::Vec2b> &mat)
{
	std::cout << "DepthImage::DepthImage(2b)" << std::endl;
	m_mat = new cv::Mat_<cv::Vec2b>(mat);
	mat.copyTo(*m_mat);
	setupGamma();
}

DepthImage::DepthImage(cv::Mat_<uint16_t> &mat)
{
	setupGamma();
	m_mat = new cv::Mat_<cv::Vec2b>(mat);
	for (int y = 0; y < 480; y++) {
		for (int x = 0; x < 640; x++) {
			(*m_mat)(y,x) = cv::Vec2b(m_gamma[mat(y,x)] >> 8, m_gamma[mat(y,x)] % 256);
		}
	}
}

DepthImage::~DepthImage()
{
	delete(m_mat);
}

cv::Mat_<cv::Vec2b> *DepthImage::cvMat()
{
	return(m_mat);
}

/*
DepthImage DepthImage::greyscaleHeatMap()
{
	return(convert(CV_8UC1, 255.0/2048.0));
}
*/

void DepthImage::filter(int up, int ud, int lp, int ld)
{
	for (int y = 0; y < 480; y++) {
		for (int x = 0; x < 640; x++) {
			if ((planeAt(x,y) > up || (planeAt(x,y) == up && depthAt(x,y) > ud))||(planeAt(x,y) < lp || (planeAt(x,y) == lp && depthAt(x,y) < ld))) {
				(*m_mat)(y,x) = cv::Vec2b(35,0);
			}
		}
	}
}

RGBImage DepthImage::diff(DepthImage &other)
{
	cv::Mat_<cv::Vec3b> newMat(m_mat->size().height, m_mat->size().width, cv::Vec3b(0,0,0));
	for (int y = 0; y < 480; y++) {
		for (int x = 0; x < 640; x++) {
			int p1 = planeAt(x,y);
			int p2 = other.planeAt(x,y);
			int d1 = depthAt(x,y);
			int d2 = other.depthAt(x,y);
			int n1 = p1 * 255 + d1;
			int n2 = p2 * 255 + d2;
			int n = n1 - n2;
			if (p1 < 0 || p1 > 5 || p2 < 0 || p2 > 5) {
				n = 0;
			}
			if (n > 255) {
				n = 255;
			}
			if (n < -255) {
				n = -255;
			}
			if (n > 0) {
				newMat(y,x) = cv::Vec3b(n, 0, 0);
			} else if (n < 0) {
				newMat(y,x) = cv::Vec3b(0, 0, 0 - n);
			}
		}
	}
	return(RGBImage(newMat));
}

RGBImage DepthImage::heatMap()
{
	cv::Mat_<cv::Vec3b> newMat(m_mat->size().height, m_mat->size().width, cv::Vec3b(0,0,0));
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
	return((*m_mat)(y,x)[1]);
}

int DepthImage::planeAt(int x, int y)
{
	return((*m_mat)(y,x)[0]);
}

void DepthImage::setupGamma()
{
	for (int i = 0; i < 2048; i++)
	{
		float v = i/2048.0;
		v = powf(v, 3) * 6;
		m_gamma[i] = v * 6 * 256;
	}
}

