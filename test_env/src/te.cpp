
#include "libgesture.h"
#include "libfreenect.hpp"
#include "cv.h"
#include "highgui.h"
#include <iostream>
#include <vector>

CvMemStorage *storage = 0;
CvHaarClassifierCascade *cascade = 0;

FaceList *detect_face(GreyscaleImage &image)
{
	cvClearMemStorage(storage);
	IplImage iplGrey(*(image.cvMat()));
	FaceList *fl = new FaceList();
	CvSeq *faces = cvHaarDetectObjects(&iplGrey, cascade, storage, 1.2, 1, CV_HAAR_DO_CANNY_PRUNING, cv::Size(30,30));
	if (faces) {
		for (int i = 0; i < faces->total; i++) {
			CvRect *r = (CvRect*)cvGetSeqElem(faces,i);
			cv::Rect nr(*r);
			Face *f = new Face(nr);
			fl->insert(f);
		}
	}
	return(fl);
}

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

	FaceList *face_list = new FaceList();

	cv::Point adjustment(16, -32);

	cv::Mat_<uint16_t> depthMat(cv::Size(640,480));
	cv::Mat_<cv::Vec3b> depthf(cv::Size(640,480));
	cv::Mat_<cv::Vec3b> rgbMat(cv::Size(640, 480));

	cv::Scalar cursor_color(0,0,0);
	cv::Scalar cursor_color_diff(255,255,255);
	cv::Scalar color_red(0,0,255);
	cv::Scalar color_white(255,255,255);
	cv::Scalar color_blue(255,0,0);
	cv::Scalar color_grey(130,130,130);
	
	storage = cvCreateMemStorage(0);
	cascade = (CvHaarClassifierCascade*) cvLoad("../haarcascade_frontalface_alt.xml", 0, 0, 0);

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

		dev->getVideo(rgbMat);
		dev->getDepth(depthMat);
		RGBImage rgbImage(rgbMat);
		DepthImage depthImage(depthMat);
		
		// face detection
		GreyscaleImage greyImage = rgbImage.greyscale();

		FaceList *faces = detect_face(greyImage);
		face_list->insert(*faces);

		Face *f = face_list->best();
		int c = 0;
		if (f && !faces->contains(f)) {
			face_list->miss(f);
		}

		faces->clear();
		delete(faces);

		if (f) {
			cv::rectangle(*(rgbImage.cvMat()), f->topLeft(), f->bottomRight(), color_white, 2);
			cv::circle(*(rgbImage.cvMat()), f->center(), 3, color_white, 1);

			cv::rectangle(*(greyImage.cvMat()), f->topLeft(), f->bottomRight(), color_white, 2);
			cv::circle(*(greyImage.cvMat()), f->center(), 3, color_white, 1);


			int d = depthImage.depthAt((f->center() + adjustment).x, (f->center() + adjustment).y);
			int p = depthImage.planeAt((f->center() + adjustment).x, (f->center() + adjustment).y);
			filter_depth = d + 100;
			filter_plane = p;
			if (filter_depth > 255) {
				filter_depth = filter_depth % 255;
				filter_plane += 1;
			}

			std::cout << "FACE: @(" << f->center().x << "," << f->center().y << ") weight (" << face_list->weight(f) << ") p [" << p << "] d [" << d << "]" << std::endl;
		} else {
			std::cout << "no face detected" << std::endl;
		}
		depthImage.filter(filter_plane, filter_depth);
		RGBImage nDepthImage = depthImage.heatMap();

		if (f) {
			cv::rectangle(*(nDepthImage.cvMat()), f->topLeft() + adjustment, f->bottomRight() + adjustment, color_white, 2);
			cv::circle(*(nDepthImage.cvMat()), f->center() + adjustment, 3, color_white, 1);
		}
		// end face detection

		rgbImage.drawCrosshairs(rgb_cursor.x, rgb_cursor.y, cursor_color, 2);
		cv::imshow("rgb", *(rgbImage.cvMat()));
		cvMoveWindow("rgb", 0, 0);

		nDepthImage.drawCrosshairs(d_cursor.x, d_cursor.y, cursor_color, 2);
		cv::imshow("depth", *(nDepthImage.cvMat()));
		cvMoveWindow("depth", 640, 0);

		cv::imshow("grey", *(greyImage.cvMat()));
		cvMoveWindow("grey", 1920, 0);

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
