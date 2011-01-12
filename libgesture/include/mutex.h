
#ifndef DARMA_MUTEX_H
#define DARMA_MUTEX_H

#include "pthread.h"

class Mutex {
	public:
		Mutex();

		void lock();
		void unlock();
	
	private:
		pthread_mutex_t m_mutex;
};

#endif // DARMA_MUTEX_H
