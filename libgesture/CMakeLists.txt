SET(BUILD_SHARED_LIBS ON)

include_directories(./include	/usr/local/include/opencv2)

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
	src/facedetector.cpp
	src/pollingthread.cpp
)

target_link_libraries(gesture freenect opencv_core opencv_imgproc
	  opencv_highgui opencv_ml opencv_video opencv_features2d
		  opencv_calib3d opencv_objdetect opencv_contrib opencv_legacy
			  opencv_flann)
