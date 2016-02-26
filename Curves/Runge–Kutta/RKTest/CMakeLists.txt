cmake_minimum_required(VERSION 2.8)
project( TestRK )
#find_package( OpenCV REQUIRED )
add_executable( TestRK TestRK.c )
target_link_libraries( TestRK  )#${OpenCV_LIBS}

