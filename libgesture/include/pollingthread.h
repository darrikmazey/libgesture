
#ifndef DARMA_POLLING_THREAD_H
#define DARMA_POLLING_THREAD_H

#include <pthread.h>
#include "rgbimage.h"
#include "depthimage.h"

class PollingThread
{
	public:
		PollingThread();
		~PollingThread();

		bool start();
		bool stop();

		void threadfunc();
		static void *start_thread(void *data);

	protected:
		volatile bool m_stop;
		pthread_t m_thread;
};

#endif // DARMA_POLLING_THREAD_H

