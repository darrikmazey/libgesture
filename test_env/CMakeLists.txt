

include_directories(${libgesture_SOURCE_DIR}/libgesture/include
	/usr/local/include/libfreenect /usr/local/include/opencv2)

link_directories(${libgesture_SOURCE_DIR}/build/libgesture)

add_executable (te src/te.cpp)

target_link_libraries(te gesture opencv_core opencv_imgproc
	opencv_highgui opencv_ml opencv_video opencv_features2d
	opencv_calib3d opencv_objdetect opencv_contrib opencv_legacy
	opencv_flann)
