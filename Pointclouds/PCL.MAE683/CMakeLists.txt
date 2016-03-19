cmake_minimum_required(VERSION 2.8 FATAL_ERROR)


project(MAE683-PCL)

find_package(PCL 1.2 REQUIRED)


include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (01_pcd_read src/pcd_read.cpp)
target_link_libraries (01_pcd_read ${PCL_LIBRARIES})

add_executable (02_pcd_write src/pcd_write.cpp)
target_link_libraries (02_pcd_write ${PCL_LIBRARIES})


add_executable (03_kdtree_search src/kdtree_search.cpp)
target_link_libraries (03_kdtree_search ${PCL_LIBRARIES})

add_executable (04_iterative_closest_point src/iterative_closest_point.cpp)
target_link_libraries (04_iterative_closest_point ${PCL_LIBRARIES})


add_executable (05_estimating_sn src/estimating_sn.cpp)
target_link_libraries (05_estimating_sn ${PCL_LIBRARIES})


add_executable (06_passthroughtest src/passthroughtest.cpp)
target_link_libraries (06_passthroughtest ${PCL_LIBRARIES})


add_executable (07_voxel_grid src/voxel_grid.cpp)
target_link_libraries (07_voxel_grid ${PCL_LIBRARIES})


add_executable (08_plane_segmentation src/planar_segmentation.cpp src/viewersetting.h)
target_link_libraries (08_plane_segmentation ${PCL_LIBRARIES})

add_executable (09_cluster_extraction src/cluster_extraction.cpp)
target_link_libraries (09_cluster_extraction ${PCL_LIBRARIES})


add_executable (10_random_sample_consensus src/random_sample_consensus.cpp)
target_link_libraries (10_random_sample_consensus ${PCL_LIBRARIES})

#add_executable (11_template_alignment src/template_alignment.cpp)
#target_link_libraries (11_template_alignment ${PCL_LIBRARIES})

add_executable (11_openni_grabber_simple src/openni_grabber_simple.cpp)
target_link_libraries (11_openni_grabber_simple ${PCL_LIBRARIES})

#add_executable (12_openni_grabber src/openni_grabber.cpp)
#target_link_libraries (12_openni_grabber ${PCL_LIBRARIES})

#add_executable(kinectPCLviewer src/KinectViewer.cpp)
#target_link_libraries (kinectPCLviewer ${PCL_LIBRARIES})



set( headers

    src/common.h
    src/pcproc.h

)

set( sources

    src/openni_grabber.cpp
    src/pcproc.hpp
   
)

add_executable (12_openni_grabber  ${sources} ${headers} )
target_link_libraries (12_openni_grabber ${PCL_LIBRARIES})



# PCL 1.7

#add_executable(openni_viewer2 src/openni_viewer2.cpp)
#target_link_libraries (openni_viewer2 ${PCL_LIBRARIES})



#add_executable(people_on_a_ground_plane src/main_ground_based_people_detection.cpp)
#target_link_libraries (people_on_a_ground_plane ${PCL_LIBRARIES})


