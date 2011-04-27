
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
			Face *f = ctx->face();
			if (f) {
				DepthImage nDepth(*depthImage);
				int p = depthImage->planeAt(f->center());
				int d = depthImage->depthAt(f->center());
				nDepth.filter(p, d);
				cv::imshow("filter", (*(nDepth.heatMap().cvMat())));
				cvMoveWindow("filter", 1920, 0);
				cv::circle(*(depthImage->cvMat()), f->center(), 9, cv::Scalar(0,0,0), 3);
			}
			cv::imshow("depth", (*(depthImage->heatMap().cvMat())));
			cvMoveWindow("depth", 640, 0);
		}
		RGBImage skeleton = ctx->drawSkeleton();
		cv::imshow("skeleton", (*(skeleton.cvMat())));
		cvMoveWindow("skeleton", 1280, 0);
	}

	delete(ctx);
}
