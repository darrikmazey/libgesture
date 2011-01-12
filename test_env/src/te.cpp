
#include "libgesture.h"
#include "libfreenect.hpp"
#include "highgui.h"
#include <iostream>

int main(int argc, char **argv)
{
	cv::Mat depthMat(cv::Size(640,480), CV_16UC1);
	cv::Mat depthf(cv::Size(640,480), CV_8UC1);
	cv::Mat rgbMat(cv::Size(640,480), CV_8UC3, cv::Scalar(0));
	cv::Mat ownMat(cv::Size(640,480), CV_8UC3, cv::Scalar(0));

	Freenect::Freenect freenect;
	LGFreenectDevice &device = freenect.createDevice<LGFreenectDevice>(0);

	cv::namedWindow("rgb", CV_WINDOW_AUTOSIZE);
	cv::namedWindow("depth", CV_WINDOW_AUTOSIZE);

	device.startVideo();
	device.startDepth();

	while(1) {
		device.getVideo(rgbMat);
		device.getDepth(depthMat);

		char k = cvWaitKey(5);
		if (k == 27) {
			cvDestroyWindow("rgb");
			cvDestroyWindow("depth");
			break;
		}

		cv::imshow("rgb", rgbMat);
		depthMat.convertTo(depthf, CV_8UC1, 255.0/2048.0);
		cv::imshow("depth", depthf);
 	}

	device.stopVideo();
	device.stopDepth();
	freenect.deleteDevice(0);
	return(0);
}
