
#ifndef DARMA_GREYSCALE_IMAGE_H
#define DARMA_GREYSCALE_IMAGE_H

#include <cv.h>

//class GreyscaleImage;
//class DepthImage;

class GreyscaleImage
{
	public:
		GreyscaleImage();
		GreyscaleImage(cv::Mat_<uint8_t> &mat);

		~GreyscaleImage();

		cv::Mat_<uint8_t> *cvMat();
	
	protected:
		void setupGamma();

		uint16_t m_gamma[2048];
		cv::Mat_<uint8_t> *m_mat;
};

#endif // DARMA_GREYSCALE_IMAGE_H
