
#ifndef DARMA_DEPTHIMAGE_H
#define DARMA_DEPTHIMAGE_H

#include "lgimage.h"
#include "rgbimage.h"
#include <cv.h>

class DepthImage : public LGImage
{
	public:
		DepthImage();
		DepthImage(cv::Mat &mat);
		~DepthImage();

		DepthImage convert(int type, double alpha = 1, double beta = 0);

		DepthImage greyscaleHeatMap();
		RGBImage heatMap();
		RGBImage diff(DepthImage &other);

		int depthAt(int x, int y);
		int planeAt(int x, int y);

		void filter(int p, int d = 255);

	private:
		void fillPD();
		cv::Mat_<cv::Vec2b> *m_pdMat;
		bool m_pdFilled;
};

#endif // DARMA_DEPTHIMAGE_H
