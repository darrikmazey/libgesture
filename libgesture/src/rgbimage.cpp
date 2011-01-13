
#include "rgbimage.h"
#include <iostream>

RGBImage::RGBImage() :
	LGImage()
{
}

RGBImage::RGBImage(cv::Mat &mat) :
	LGImage(mat)
{
}

RGBImage::~RGBImage()
{
}

