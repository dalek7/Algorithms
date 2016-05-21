cmake_minimum_required(VERSION 2.8)
project( FlannTest )
find_package( OpenCV REQUIRED )
add_executable( FlannTest FlannTest.cpp )
target_link_libraries( FlannTest ${OpenCV_LIBS} )

