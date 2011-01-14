
#ifndef DARMA_FACE_LIST_H
#define DARMA_FACE_LIST_H

#include "face.h"
#include <map>

class FaceList
{
	public:
		FaceList(int mt = 50, float r = 0.125, int mm = 5);
		~FaceList();

		int insert(Face *f, int weight = 1);
		int insert(FaceList &other);

		int miss(Face *f);
		int remove(Face *f);
		void clear();

		Face *best();

		int weight(Face *f);
		bool contains(Face *f);
		bool containsExactly(Face *f);
		Face *match(Face *f);
		int size();

		int matchThreshold();
		float certaintyRatio();

	protected:
		void findBest();
		void prune();

		std::map< Face*, int > m_faces;
		std::map< Face*, int > m_misses;
		Face * m_best;
		int m_matchThreshold;
		float m_ratio;
		int m_maxMisses;
};

#endif // DARMA_FACE_LIST_H
