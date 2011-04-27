
#ifndef DARMA_DEPTHIMAGE_H
#define DARMA_DEPTHIMAGE_H

#include <opencv.hpp>

class RGBImage;

class DepthImage
{
	public:
		DepthImage();
		DepthImage(cv::Mat2b &mat);
		DepthImage(cv::Mat_<uint16_t> &mat);
		DepthImage(DepthImage &other);
		~DepthImage();

		/*
		DepthImage greyscaleHeatMap();
		*/

		void filter(int up, int ud, int lp = 0, int ld = 0);

		RGBImage heatMap();

		int depthAt(int x, int y);
		int depthAt(const cv::Point &p);
		int planeAt(int x, int y);
		int planeAt(const cv::Point &p);

		int frame();

		cv::Mat2b *cvMat();

	private:
		void setupGamma();

		cv::Mat2b *m_mat;
		uint16_t m_gamma[2048];
		int m_frame;
};

#endif // DARMA_DEPTHIMAGE_H
