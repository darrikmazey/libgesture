
#ifndef DARMA_RGBIMAGE_H
#define DARMA_RGBIMAGE_H

#include "lgimage.h"
#include <cv.h>

class RGBImage : public LGImage
{
	public:
		RGBImage();
		RGBImage(cv::Mat &mat);
		~RGBImage();
};

#endif // DARMA_RGBIMAGE_H
