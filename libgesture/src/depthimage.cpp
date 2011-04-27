
#include "depthimage.h"
#include "rgbimage.h"
#include <iostream>

DepthImage::DepthImage()
{
	m_mat = 0;
	setupGamma();
}

DepthImage::DepthImage(cv::Mat2b &mat)
{
	//std::cout << "DepthImage::DepthImage(2b)" << std::endl;
	m_mat = new cv::Mat2b(mat.clone());
	setupGamma();
}

DepthImage::DepthImage(DepthImage &other)
{
	//std::cout << "DepthImage::DepthImage(other)" << std::endl;
	m_mat = new cv::Mat2b(other.cvMat()->clone());
	m_frame = other.frame();
	setupGamma();
}

DepthImage::DepthImage(cv::Mat_<uint16_t> &mat)
{
	//std::cout << "DepthImage::DepthImage(uint16_t)" << std::endl;
	static int frame = 0;
	m_frame = frame;
	frame++;
	setupGamma();
	m_mat = new cv::Mat2b(mat.clone());
	for (int y = 0; y < 480; y++) {
		for (int x = 0; x < 640; x++) {
			uint16_t n = m_gamma[(uint16_t)(mat(y,x))];
			int p = n >> 8;
			int d = n % 256;
			////std::cout << "(" << x << "," << y << ") [" << n << ": " << p << "," << d << "]" << std::endl;
			(*m_mat)(y,x) = cv::Vec2b(p,d);
			////std::cout << "(" << x << "," << y << ") [" << (int)(*m_mat)(y,x)[0] << "," << (int)(*m_mat)(y,x)[1] << "]" << std::endl;
		}
	}
}

DepthImage::~DepthImage()
{
	delete(m_mat);
}

cv::Mat2b *DepthImage::cvMat()
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

int DepthImage::frame()
{
	return(m_frame);
}

RGBImage DepthImage::heatMap()
{
	cv::Mat3b newMat(m_mat->size().height, m_mat->size().width, cv::Vec3b(0,0,0));
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
	RGBImage img(newMat);
	return(img);
}

int DepthImage::depthAt(int x, int y)
{
	if (x == 320 && y == 240) {
		//std::cout << "depthAt(320,240) frame (" << m_frame << ")" << std::endl;
	}
	return((*m_mat)(y,x)[1]);
}

int DepthImage::depthAt(const cv::Point &p)
{
	return(depthAt(p.x, p.y));
}

int DepthImage::planeAt(int x, int y)
{
	if (x == 320 && y == 240) {
		//std::cout << "planeAt(320,240) frame (" << m_frame << ")" << std::endl;
	}
	return((*m_mat)(y,x)[0]);
}

int DepthImage::planeAt(const cv::Point &p)
{
	return(planeAt(p.x, p.y));
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

