
#include "libgesture.h"
#include "libfreenect.hpp"
#include "cv.h"
#include "highgui.h"
#include <iostream>

int main(int argc, char **argv)
{
	GestureContext *ctx = LibGesture::init();

	LGFreenectDevice *dev = ctx->device();
	
	cv::Point rgb_cursor(320,240);
	cv::Point d_cursor(320,240);

	int filter_depth = 255;
	int filter_plane = 4;

	bool haveLastDepth = false;
	DepthImage *lastDepth;

	cv::Mat depthMat(cv::Size(640,480), CV_16UC1);
	cv::Mat depthf(cv::Size(640,480), CV_8UC1);
	cv::Mat rgbMat(cv::Size(640, 480), CV_8UC3);

	cv::Scalar cursor_color(0,0,0);
	cv::Scalar cursor_color_diff(255,255,255);

	while (char k = cvWaitKey(10)) {
		if (k == 27) {
			break;
		}
		switch(k) {
			case 105:
				rgb_cursor.y = rgb_cursor.y - 1;
				break;
			case 109:
				rgb_cursor.y = rgb_cursor.y + 1;
				break;
			case 106:
				rgb_cursor.x = rgb_cursor.x - 1;
				break;
			case 107:
				rgb_cursor.x = rgb_cursor.x + 1;
				break;
			case 119:
				d_cursor.y = d_cursor.y - 1;
				break;
			case 120:
				d_cursor.y = d_cursor.y + 1;
				break;
			case 97:
				d_cursor.x = d_cursor.x - 1;
				break;
			case 115:
				d_cursor.x = d_cursor.x + 1;
				break;
			case 80:
				filter_plane = filter_plane + 1;
				if (filter_plane > 4) {
					filter_plane = 4;
				}
				filter_depth = 255;
				break;
			case 87:
				filter_plane = filter_plane - 1;
				if (filter_plane < -1) {
					filter_plane = -1;
				}
				filter_depth = 255;
				break;
			case 85:
				filter_depth = filter_depth + 1;
				if (filter_depth > 255) {
					filter_depth = 0;
					filter_plane = filter_plane + 1;
					if (filter_plane > 4) {
						filter_plane = 4;
					}
				}
				break;
			case 86:
				filter_depth = filter_depth - 1;
				if (filter_depth < 0) {
					filter_depth = 255;
					filter_plane = filter_plane - 1;
					if (filter_plane < -1) {
						filter_plane = -1;
					}
				}
				break;
			case -1:
				break;
			default:
				std::cout << "unknown key: " << (int)k << std::endl;
				break;
		}

		//std::cout << "diff: (" << (d_cursor.x - rgb_cursor.x) << "," << (d_cursor.y - rgb_cursor.y) << ")" << std::endl;
		std::cout << "filter [" << filter_plane << " : " << filter_depth << "]" << std::endl;

		dev->getVideo(rgbMat);
		dev->getDepth(depthMat);
		RGBImage rgbImage(rgbMat);
		DepthImage depthImage(depthMat);
		
		//std::cout << "[" << depthImage.planeAt(d_cursor.x, d_cursor.y) << " : " << depthImage.depthAt(d_cursor.x, d_cursor.y) << "]" << std::endl;

		rgbImage.drawCrosshairs(rgb_cursor.x, rgb_cursor.y, cursor_color, 2);
		cv::imshow("rgb", *(rgbImage.cvMat()));
		cvMoveWindow("rgb", 0, 0);
		
		depthImage.filter(filter_plane, filter_depth);
		RGBImage nDepthImage = depthImage.heatMap();
		nDepthImage.drawCrosshairs(d_cursor.x, d_cursor.y, cursor_color, 2);
		cv::imshow("depth", *(nDepthImage.cvMat()));
		cvMoveWindow("depth", 640, 0);

		if (haveLastDepth) {
			RGBImage diffImage = depthImage.diff(*lastDepth);
			diffImage.drawCrosshairs(d_cursor.x, d_cursor.y, cursor_color_diff, 2);
			DepthImage *old_last_depth = lastDepth;
			lastDepth = new DepthImage(*(depthImage.cvMat()));
			delete(old_last_depth);
			cv::imshow("diff", *(diffImage.cvMat()));
			cvMoveWindow("diff", 1280, 0);
		} else {
			lastDepth = new DepthImage(*(depthImage.cvMat()));
			haveLastDepth = true;
		}
	}

	delete(ctx);
}
