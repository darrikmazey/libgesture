
#include "libgesture.h"
#include "libfreenect.hpp"
#include "highgui.h"
#include <iostream>

int main(int argc, char **argv)
{
	GestureContext *ctx = LibGesture::init();
	delete(ctx);
}
