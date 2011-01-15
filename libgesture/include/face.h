
#ifndef DARMA_FACE_H
#define DARMA_FACE_H

#include <opencv.hpp>

class Face {
	public:
		Face();
		Face(cv::Rect &rect);
		~Face();

		cv::Point center();
		int width();
		int height();
		cv::Point topLeft();
		cv::Point bottomRight();
		int weight();
		void setWeight(int w);
		void adjustCenter(cv::Point other_center);

		bool contains(cv::Point &p);
		bool matches(Face &other, int threshold = 25);
	
	protected:
		cv::Point m_center;
		int m_width;
		int m_height;
		int m_weight;
};

#endif // DARMA_FACE_H
