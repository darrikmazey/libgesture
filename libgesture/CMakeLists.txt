SET(BUILD_SHARED_LIBS ON)

include_directories(./include /usr/local/include/libfreenect
	/usr/include/opencv)

add_library (gesture src/mutex.cpp src/lgfreenectdevice.cpp
	src/gesturecontext.cpp src/libgesture.cpp)

target_link_libraries(gesture freenect)
