
#include "libgesture.h"
#include <iostream>
#include <opencv.hpp>

int main(int argc, char **argv)
{
	GestureContext *ctx = LibGesture::init();

	RGBImage *rgbImage = 0;
	DepthImage *depthImage = 0;
	while(1) {
		char k = -1;
		k = cvWaitKey(10);
		if (k == 27) {
			break;
		}
		if (rgbImage) {
			delete(rgbImage);
			rgbImage = 0;
		}
		if (depthImage) {
			delete(depthImage);
			depthImage = 0;
		}
		rgbImage = ctx->lastRGBImage();
		depthImage = ctx->lastDepthImage();
		if (rgbImage) {
			cv::imshow("rgb", (*(rgbImage->cvMat())));
			cvMoveWindow("rgb", 0, 0);
		}
		if (depthImage) {
			cv::imshow("depth", (*(depthImage->heatMap().cvMat())));
			cvMoveWindow("depth", 640, 0);
		}
	}

	delete(ctx);
}
