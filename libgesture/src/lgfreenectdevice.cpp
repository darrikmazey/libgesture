
#include "lgfreenectdevice.h"
#include <iostream>

LGFreenectDevice::LGFreenectDevice(freenect_context *_ctx, int _index)
	: Freenect::FreenectDevice(_ctx, _index), m_buffer_depth(640*480*1),m_buffer_rgb(FREENECT_VIDEO_RGB_SIZE), m_gamma(2048), m_new_rgb_frame(false), m_new_depth_frame(false),
	depthMat(cv::Size(640,480),0), rgbMat(cv::Size(640,480),cv::Vec3b(0,0,0))
{
	for( unsigned int i = 0 ; i < 2048 ; i++) {
		float v = i/2048.0;
		v = std::pow(v, 3)* 6;
		m_gamma[i] = v*6*256;
	}
}

void LGFreenectDevice::VideoCallback(void* _rgb, uint32_t timestamp)
{
	static int frame = 0;
	frame++;
	//std::cout << "RGB callback (frame " << frame << ")" << std::endl;
	m_rgb_mutex.lock();
	uint8_t* rgb = static_cast<uint8_t*>(_rgb);
	std::copy(rgb, rgb+getVideoBufferSize(), m_buffer_rgb.begin());
	cv::Mat_<cv::Vec3b> nMat(rgbMat);
	nMat.data = (uchar *) &m_buffer_rgb.front();
	nMat.copyTo(rgbMat);
	m_new_rgb_frame = true;
	m_rgb_mutex.unlock();
	//std::cout << "end callback" << std::endl;
}

void LGFreenectDevice::DepthCallback(void* _depth, uint32_t timestamp)
{
	static int frame = 0;
	frame++;
	//std::cout << "Depth callback (frame " << frame << ")" << std::endl;
	m_depth_mutex.lock();
	uint16_t* depth = static_cast<uint16_t*>(_depth);
	std::copy(depth, depth+(640*480*1), m_buffer_depth.begin());
	cv::Mat_<cv::Vec2b> nMat(depthMat);
	nMat.data = (uchar*) &m_buffer_depth.front();
	nMat.copyTo(depthMat);
	m_new_depth_frame = true;
	m_depth_mutex.unlock();
	//std::cout << "end callback" << std::endl;
}

bool LGFreenectDevice::getVideo(cv::Mat& output)
{
	m_rgb_mutex.lock();
	if(m_new_rgb_frame) {
		cv::cvtColor(rgbMat, output, CV_RGB2BGR);
		m_new_rgb_frame = false;
		m_rgb_mutex.unlock();
		return true;
	} else {
		m_rgb_mutex.unlock();
		return false;
	}
}

bool LGFreenectDevice::getDepth(cv::Mat& output)
{
	m_depth_mutex.lock();
	if(m_new_depth_frame) {
		depthMat.copyTo(output);
		m_new_depth_frame = false;
		m_depth_mutex.unlock();
		return true;
	} else {
		m_depth_mutex.unlock();
		return false;
	}
}

