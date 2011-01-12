

include_directories(${libgesture_SOURCE_DIR}/libgesture/include
	/usr/local/include/libfreenect /usr/include/opencv)

link_directories(${libgesture_SOURCE_DIR}/build/libgesture)

add_executable (te src/te.cpp)

target_link_libraries(te gesture cxcore cv highgui cvaux ml)
