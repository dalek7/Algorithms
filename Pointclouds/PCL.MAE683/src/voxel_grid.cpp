#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>

//http://www.pointclouds.org/documentation/tutorials/voxel_grid.php
// TODO : http://pointclouds.org/documentation/tutorials/supervoxel_clustering.php


boost::shared_ptr<pcl::visualization::PCLVisualizer>
simpleVis (pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud)
{
  // --------------------------------------------
  // -----Open 3D viewer and add point cloud-----
  // --------------------------------------------
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
  viewer->setBackgroundColor (0, 0, 0);
  viewer->addPointCloud<pcl::PointXYZ> (cloud, "sample cloud");
  viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");
  //viewer->addCoordinateSystem (1.0);
  viewer->initCameraParameters ();
  return (viewer);
}


boost::shared_ptr<pcl::visualization::PCLVisualizer>
simpleVis3(pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr cloud)
{
  // --------------------------------------------
  // -----Open 3D viewer and add point cloud-----
  // --------------------------------------------
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer (new pcl::visualization::PCLVisualizer ("3D Viewer"));
  viewer->setBackgroundColor (0, 0, 0);

  pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGBA> rgb(cloud);
  viewer->addPointCloud<pcl::PointXYZRGBA> (cloud, rgb, "sample cloud");
  
  viewer->setPointCloudRenderingProperties (pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud");
 
  //viewer->addCoordinateSystem (1.0);
  viewer->initCameraParameters ();
  return (viewer);
}

void setView1(pcl::visualization::PCLVisualizer& viewer);


int
main (int argc, char** argv)
{

  pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGBA>);
  pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZRGBA>);


  // Fill in the cloud data
  pcl::PCDReader reader;
  // Replace the path below with the path where you saved your file
  reader.read ("../res/MAE.pcd", *cloud); // Remember to download the file first!
  //
  //table_scene_lms400

  
  std::cerr << "PointCloud before filtering: " << cloud->width * cloud->height 
       << " data points (" << pcl::getFieldsList (*cloud) << ")." <<std::endl<<std::endl;


  // Create the filtering object
  pcl::VoxelGrid<pcl::PointXYZRGBA> sor;
  sor.setInputCloud (cloud);
  float leafsize = 0.015f;
  sor.setLeafSize (leafsize, leafsize, leafsize);
  sor.filter (*cloud_filtered);

  std::cerr << "PointCloud after filtering: " << cloud_filtered->width * cloud_filtered->height
       << " data points (" << pcl::getFieldsList (*cloud_filtered) << ").";


  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
  viewer = simpleVis3(cloud_filtered);
  setView1(*viewer);

  char ch[255];
  sprintf(ch, "Leaf size= (%.3f,%.3f,%.3f)", leafsize, leafsize, leafsize);;
  viewer->addText(ch, 10,520-20,15,1,1,1);
  //viewer->addText("Original", 10,520-20,15,1,1,1);

  
  while (!viewer->wasStopped ())
  {
    viewer->spinOnce ();
  }


  //pcl::PCDWriter writer;
  //writer.write ("../res/table_scene_lms400_downsampled.pcd", *cloud_filtered,
  //       Eigen::Vector4f::Zero (), Eigen::Quaternionf::Identity (), false);



  return (0);
}



/*

0.00393101,3.93101/-0.022696,0.169112,0.356029/-0.0259827,0.428571,-0.0275477/-0.030215,-0.828045,-0.559847/0.523599/960,520/0,0

*/
void setView1(pcl::visualization::PCLVisualizer& viewer)
{

    viewer.camera_.clip[0] = 0.00393101;
    viewer.camera_.clip[1] = 3.93101;
    viewer.camera_.focal[0] = -0.022696;
    viewer.camera_.focal[1] = 0.169112;
    viewer.camera_.focal[2] = 0.356029;

    viewer.camera_.pos[0] = -0.0259827;
    viewer.camera_.pos[1] = 0.428571;
    viewer.camera_.pos[2] = -0.0275477;

    viewer.camera_.view[0] = -0.030215;
    viewer.camera_.view[1] = -0.828045;
    viewer.camera_.view[2] = -0.559847;

    viewer.camera_.fovy = 0.523599;
    viewer.camera_.window_size[0] = 960;
    viewer.camera_.window_size[1] = 520;
    viewer.camera_.window_pos[0] = 0;
    viewer.camera_.window_pos[1] = 0;

    viewer.updateCamera();

}
