#include <iostream>
#include <pcl/ModelCoefficients.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>

#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>

//http://www.pointclouds.org/documentation/tutorials/planar_segmentation.php

#include "viewersetting.h"

int
 main (int argc, char** argv)
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);

    //pcl::PointCloud<pcl::PointXYZ> cloud;

    if (pcl::io::loadPCDFile<pcl::PointXYZ> ("../res/milk_cartoon_all_small_clorox.pcd", *cloud) == -1)
    {
        PCL_ERROR ("Couldn't read file test_pcd.pcd \n");
        return (-1);
    }
    std::cout << "Loaded "
            << cloud->width * cloud->height
            << " data points from test_pcd.pcd"
            << std::endl;


  std::cerr << "Point cloud data: " << cloud->points.size () << " points" << std::endl;

  pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients);
  pcl::PointIndices::Ptr inliers (new pcl::PointIndices);

  // Create the segmentation object
  pcl::SACSegmentation<pcl::PointXYZ> seg;

  // Optional
  seg.setOptimizeCoefficients (true);

  // Mandatory
  seg.setModelType (pcl::SACMODEL_PLANE);
  seg.setMethodType (pcl::SAC_RANSAC);
  seg.setDistanceThreshold (0.01);

  seg.setInputCloud (cloud->makeShared ());
  seg.segment (*inliers, *coefficients);

  if (inliers->indices.size () == 0)
  {
    PCL_ERROR ("Could not estimate a planar model for the given dataset.");
    return (-1);
  }

  int* indextemp = new int [cloud->size()];
  for (size_t i = 0; i<cloud->size(); i++)
  {
      indextemp[i] =0;

  }

  //construct the table
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_plane (new pcl::PointCloud<pcl::PointXYZ>);
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_others (new pcl::PointCloud<pcl::PointXYZ>);


  for (size_t i = 0; i < inliers->indices.size (); ++i)
  {
    pcl::PointXYZ v1 = cloud->points[inliers->indices[i]];
    //v1.y = v1.y - 0.0007;

    cloud_plane->push_back(v1);

    indextemp[inliers->indices[i]] =1;
  }

  for (size_t i = 0; i<cloud->size(); i++)
  {
      if(indextemp[i] ==0)
      {
           pcl::PointXYZ v1 = cloud->points[i];

           cloud_others->push_back(v1);
      }
  }

  delete[] indextemp;
  indextemp = NULL;


  pcl::visualization::PCLVisualizer viewer("PCL Viewer");
    //pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(cloud);

  viewer.setBackgroundColor (0.0, 0.0, 0.5);

  setView1(viewer);


  //display segmented view

  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color(cloud_others, 0, 255, 0);
  viewer.addPointCloud<pcl::PointXYZ> (cloud_others, single_color, "sample cloud");

  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color2(cloud_plane, 255, 0, 255);
  viewer.addPointCloud<pcl::PointXYZ> (cloud_plane, single_color2, "sample cloud2");


  std::cerr << "Model coefficients: " << coefficients->values[0] << " "
                                      << coefficients->values[1] << " "
                                      << coefficients->values[2] << " "
                                      << coefficients->values[3] << std::endl;

  std::cerr << "Plane: "    << coefficients->values[0] << "x+"
                            << coefficients->values[1] << "y+"
                            << coefficients->values[2] << "z+"
                            << coefficients->values[3] << "=0" << std::endl;

  //printf("%.2fx+%.2fy+%.2fz%.2f=0"  , coefficients->values[0]
  //                                  , coefficients->values[1]
  //                                  , coefficients->values[2]
  //                                  , coefficients->values[3]);

  std::cerr << "Model inliers: " << inliers->indices.size () << std::endl;
  if(0)
  for (size_t i = 0; i < inliers->indices.size (); ++i)
   std::cerr << inliers->indices[i] << "    " << cloud->points[inliers->indices[i]].x << " "
                                               << cloud->points[inliers->indices[i]].y << " "
                                               << cloud->points[inliers->indices[i]].z << std::endl;


  while (!viewer.wasStopped ())
  {
    viewer.spinOnce ();
  }





  return (0);
}


