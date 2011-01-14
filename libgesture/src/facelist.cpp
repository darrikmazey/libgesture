
#include "facelist.h"
#include <iostream>

FaceList::FaceList(int mt, float r, int mm)
{
	m_best = 0;
	m_matchThreshold = mt;
	m_ratio = r;
	m_maxMisses = mm;
}

FaceList::~FaceList()
{
	for (std::map< Face*, int >::iterator it = m_faces.begin(); it != m_faces.end(); it++) {
		delete(it->first);
	}
}

int FaceList::matchThreshold()
{
	return(m_matchThreshold);
}

float FaceList::certaintyRatio()
{
	return(m_ratio);
}

bool FaceList::contains(Face *f)
{
	if (!(m_faces.find(f) == m_faces.end())) {
		return(true);
	}
	for (std::map< Face*, int >::iterator it = m_faces.begin(); it != m_faces.end(); it++) {
		Face *oldface = it->first;
		if (f->matches(*oldface, m_matchThreshold)) {
			return(true);
		}
	}
	return(false);
}

Face *FaceList::match(Face *f)
{
	if (!contains(f)) {
		return(0);
	}
	if (containsExactly(f)) {
		return(f);
	}
	for (std::map< Face*, int >::iterator it = m_faces.begin(); it != m_faces.end(); it++) {
		Face *oldface = it->first;
		if (f->matches(*oldface, m_matchThreshold)) {
			return(oldface);
		}
	}
	return(0);
}

bool FaceList::containsExactly(Face *f)
{
	return(!(m_faces.find(f) == m_faces.end()));
}

int FaceList::size()
{
	return(m_faces.size());
}

int FaceList::insert(FaceList &other)
{
	for (std::map< Face*, int >::iterator it = other.m_faces.begin(); it != other.m_faces.end(); it++) {
		insert(it->first, it->second);
	}
	return(other.size());
}

int FaceList::insert(Face *f, int weight)
{
	if (contains(f)) {
		Face *mf = match(f);
		mf->adjustCenter(f->center());
		int w = m_faces[mf] + weight;
		m_faces[mf] = w;
		m_misses[mf] = 0;
		findBest();
		return(m_faces[mf]);
	}
	m_faces[f] = weight;
	m_misses[f] = 0;
	findBest();
	return(weight);
}

int FaceList::miss(Face *f)
{
	if (containsExactly(f)) {
		m_misses[f] = m_misses[f] + 1;
		int r = m_misses[f];
		findBest();
		return(r);
	} else {
		return(0);
	}
}

int FaceList::remove(Face *f)
{
	if (containsExactly(f)) {
		int w = m_faces[f];
		m_faces.erase(f);
		findBest();
		return(w);
	}
	return(0);
}

void FaceList::clear()
{
	m_faces.clear();
}

Face *FaceList::best()
{
	return(m_best);
}

int FaceList::weight(Face *f)
{
	if (!f) {
		return(1);
	}
	if (contains(f)) {
		return(m_faces[f]);
	}
	return(0);
}

void FaceList::findBest()
{
	int max = 0;
	m_best = 0;
	for (std::map< Face*, int >::iterator it = m_faces.begin(); it != m_faces.end(); it++ ) {
		if (m_misses.find(it->first) == m_misses.end() || m_misses[it->first] <= m_maxMisses) {
			if (it->second > max) {
				m_best = it->first;
				max = it->second;
			}
		}
	}
	prune();
}

void FaceList::prune()
{
	int w = weight(m_best);
	int i = 0;
	for (std::map< Face*, int >::iterator it = m_faces.begin(); it != m_faces.end(); it++ ) {
		if ((it->second / (float)w) < (m_ratio)) {
			m_misses.erase(it->first);
			delete(it->first);
			m_faces.erase(it);
			i++;
		} else if (m_misses.find(it->first) != m_misses.end() && m_misses[it->first] > m_maxMisses) {
			m_misses.erase(it->first);
			delete(it->first);
			m_faces.erase(it);
			i++;
		}
	}
}

