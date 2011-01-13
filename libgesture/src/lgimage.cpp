
#include "lgimage.h"
#include <iostream>

LGImage::LGImage()
{
	m_mat = 0;
	setupGamma();
}

LGImage::LGImage(cv::Mat &mat)
{
	m_mat = new cv::Mat(mat);
	mat.copyTo(*m_mat);
	setupGamma();
}

LGImage::~LGImage()
{
	delete(m_mat);
}

cv::Mat *LGImage::cvMat()
{
	return(m_mat);
}

void LGImage::drawCrosshairs(int x, int y, cv::Scalar &color, int thickness, int lineType, int shift)
{
	line(*m_mat, cv::Point(x-5, y), cv::Point(x+5, y), color, thickness, lineType, shift);
	line(*m_mat, cv::Point(x, y-5), cv::Point(x, y+5), color, thickness, lineType, shift);
}

void LGImage::setupGamma()
{
	for (int i = 0; i < 2048; i++)
	{
		float v = i/2048.0;
		v = powf(v, 3) * 6;
		m_gamma[i] = v * 6 * 256;
	}
}

