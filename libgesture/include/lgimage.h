
#ifndef DARMA_LGIMAGE_H
#define DARMA_LGIMAGE_H

#include <cv.h>

class LGImage
{
	public:
		LGImage();
		LGImage(cv::Mat &mat);
		~LGImage();

		cv::Mat *cvMat();

		void drawCrosshairs(int x, int y, cv::Scalar &color, int thickness = 1, int lineType = 8, int shift = 0);

	protected:
		void setupGamma();

		cv::Mat *m_mat;
		uint16_t m_gamma[2048];
};

#endif // DARMA_LGIMAGE_H
