
#ifndef DARMA_GREYSCALE_IMAGE_H
#define DARMA_GREYSCALE_IMAGE_H

#include <opencv.hpp>

//class GreyscaleImage;
//class DepthImage;

class GreyscaleImage
{
	public:
		GreyscaleImage();
		GreyscaleImage(cv::Mat1b &mat);

		~GreyscaleImage();

		cv::Rect clipRect(cv::Rect &r);
		cv::Rect clipRect(const cv::Rect &r);

		cv::Mat1b *cvMat();
	
	protected:
		void setupGamma();

		uint16_t m_gamma[2048];
		cv::Mat1b *m_mat;
};

#endif // DARMA_GREYSCALE_IMAGE_H
