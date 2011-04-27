
#include "face.h"
#include <iostream>

Face::Face()
{
}

Face::Face(cv::Rect &r)
{
	cv::Point tl = r.tl();
	m_center = cv::Point(tl.x + r.width/2, tl.y + r.height/2);
	m_width = r.width;
	m_height = r.height;
	m_weight = 1;
}

Face::~Face()
{
}

cv::Point Face::center()
{
	return(m_center);
}

int Face::width()
{
	return(m_width);
}

int Face::height()
{
	return(m_height);
}

cv::Point Face::topLeft()
{
	return(cv::Point(m_center.x - m_width/2, m_center.y - m_height/2));
}

cv::Point Face::bottomRight()
{
	return(cv::Point(m_center.x + m_width/2, m_center.y + m_height/2));
}

cv::Rect Face::boundingRect()
{
	return(cv::Rect(topLeft(), bottomRight()));
}

cv::Rect Face::detectionRect()
{
	return(cv::Rect(cv::Point(topLeft().x - m_width/2, topLeft().y - m_height/2), cv::Point(bottomRight().x + m_width/2, bottomRight().y + m_height/2)));
}

int Face::weight()
{
	return(m_weight);
}

void Face::setWeight(int w)
{
	m_weight = w;
}

void Face::adjustCenter(cv::Point other_center)
{
	//m_center = cv::Point((m_center.x + other_center.x)/2, (m_center.y + other_center.y)/2);
	m_center = other_center;
}

bool Face::contains(cv::Point &p)
{
	if (p.x >= topLeft().x && p.x <= bottomRight().x && p.y >= topLeft().y && p.y <= bottomRight().y) {
		return(true);
	} else {
		return(false);
	}
}

bool Face::matches(Face &other, int threshold)
{
	cv::Point tl(m_center.x - threshold, m_center.y - threshold);
	cv::Point br(m_center.x + threshold, m_center.y + threshold);
	cv::Point oc(other.center());
	if (oc.x >= tl.x && oc.x <= br.x && oc.y >= tl.y && oc.y <= br.y) {
		return(true);
	} else {
		return(false);
	}
}
