
#ifndef DARMA_RGBIMAGE_H
#define DARMA_RGBIMAGE_H

#include <opencv.hpp>

class GreyscaleImage;
//class DepthImage;

class RGBImage
{
	public:
		RGBImage();
		RGBImage(cv::Mat3b &mat);
		RGBImage(RGBImage &other);
		RGBImage(const RGBImage &other);
		~RGBImage();

		GreyscaleImage greyscale();
		void mask(RGBImage &mask);
//		void mask(DepthImage &mask);

		void drawCrosshairs(int x, int y, cv::Scalar &color, int thickness = 1, int lineType = 8, int shift = 0);

		cv::Mat3b *cvMat() const;
	
	protected:
		void setupGamma();

		uint16_t m_gamma[2048];
		cv::Mat3b *m_mat;
};

#endif // DARMA_RGBIMAGE_H
