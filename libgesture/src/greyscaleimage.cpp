
#include "greyscaleimage.h"
#include <iostream>

GreyscaleImage::GreyscaleImage()
{
	m_mat = 0;
	setupGamma();
}

GreyscaleImage::GreyscaleImage(cv::Mat1b &mat)
{
	m_mat = new cv::Mat1b(mat.clone());
	setupGamma();
}

GreyscaleImage::~GreyscaleImage()
{
	delete(m_mat);
}

cv::Mat1b *GreyscaleImage::cvMat()
{
	return(m_mat);
}

cv::Rect GreyscaleImage::clipRect(cv::Rect &r)
{
	int nx1 = r.tl().x;
	int ny1 = r.tl().y;
	int nx2 = r.br().x;
	int ny2 = r.br().y;
	if (nx1 < 0) {
		nx1 = 0;
	}
	if (nx1 > m_mat->cols) {
		nx1 = m_mat->cols;
	}
	if (ny1 < 0) {
		ny1 = 0;
	}
	if (ny1 > m_mat->rows) {
		ny1 = m_mat->rows;
	}
	if (nx2 < 0) {
		nx2 = 0;
	}
	if (nx2 > m_mat->cols) {
		nx2 = m_mat->cols;
	}
	if (ny2 < 0) {
		ny2 = 0;
	}
	if (ny2 > m_mat->rows) {
		ny2 = m_mat->rows;
	}
	return(cv::Rect(cv::Point(nx1, ny1), cv::Point(nx2, ny2)));
}

cv::Rect GreyscaleImage::clipRect(const cv::Rect &r)
{
	int nx1 = r.tl().x;
	int ny1 = r.tl().y;
	int nx2 = r.br().x;
	int ny2 = r.br().y;
	if (nx1 < 0) {
		nx1 = 0;
	}
	if (nx1 > m_mat->cols) {
		nx1 = m_mat->cols;
	}
	if (ny1 < 0) {
		ny1 = 0;
	}
	if (ny1 > m_mat->rows) {
		ny1 = m_mat->rows;
	}
	if (nx2 < 0) {
		nx2 = 0;
	}
	if (nx2 > m_mat->cols) {
		nx2 = m_mat->cols;
	}
	if (ny2 < 0) {
		ny2 = 0;
	}
	if (ny2 > m_mat->rows) {
		ny2 = m_mat->rows;
	}
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
