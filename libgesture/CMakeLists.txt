SET(BUILD_SHARED_LIBS ON)

include_directories(./include	/usr/include/opencv)

add_library (gesture
	src/mutex.cpp
	src/lgfreenectdevice.cpp
	src/gesturecontext.cpp
	src/libgesture.cpp
	src/rgbimage.cpp
	src/depthimage.cpp
	src/greyscaleimage.cpp
	src/face.cpp
	src/facelist.cpp
)

target_link_libraries(gesture freenect)
