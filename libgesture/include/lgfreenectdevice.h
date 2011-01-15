
#ifndef DARMA_LG_FREENECT_DEVICE
#define DARMA_LG_FREENECT_DEVICE

#include <libfreenect.hpp>
#include "mutex.h"
#include <opencv.hpp>
#include <iostream>

class LGFreenectDevice : public Freenect::FreenectDevice
{
	public:
		LGFreenectDevice(freenect_context *_ctx, int _index);

		// Do not call directly even in child
		void VideoCallback(void* _rgb, uint32_t timestamp);

		// Do not call directly even in child
		void DepthCallback(void* _depth, uint32_t timestamp);

		bool getVideo(cv::Mat& output);

		bool getDepth(cv::Mat& output);

	private:
		std::vector<uint16_t> m_buffer_depth;
		std::vector<uint8_t> m_buffer_rgb;
		std::vector<uint16_t> m_gamma;
		cv::Mat_<cv::Vec2b> depthMat;
		cv::Mat_<cv::Vec3b> rgbMat;
		Mutex m_rgb_mutex;
		Mutex m_depth_mutex;
		bool m_new_rgb_frame;
		bool m_new_depth_frame;

};



#endif // DARMA_LG_FREENECT_DEVICE

