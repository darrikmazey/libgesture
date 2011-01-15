
#include "libgesture.h"
#include <iostream>

int main(int argc, char **argv)
{
	GestureContext *ctx = LibGesture::init();

	while(1) {
		static int c = 0;
		std::cout << "iteration " << c++ << std::endl;
		sleep(5);
	}

	delete(ctx);
}
