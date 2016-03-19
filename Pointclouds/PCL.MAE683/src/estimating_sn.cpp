#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/features/normal_3d.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/common/pca.h>


int main (int argc, char** argv)
{
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);

//  ... read, pass in or create a point cloud ...
    if (pcl::io::loadPCDFile<pcl::PointXYZ> ("../res/bunny.pcd", *cloud) == -1) //* load the file
    {
        PCL_ERROR ("Couldn't read file test_pcd.pcd \n");
        return (-1);
    }
    std::cout << "Loaded "
            << cloud->width * cloud->height
            << " data points from test_pcd.pcd"
            << std::endl;


    // Placeholder for the 3x3 covariance matrix at each surface patch
    Eigen::Matrix3f covariance_matrix;
    // 16-bytes aligned placeholder for the XYZ centroid of a surface patch
    Eigen::Vector4f xyz_centroid;

    // Estimate the XYZ centroid
    compute3DCentroid(*cloud, xyz_centroid);

    // Compute the 3x3 covariance matrix
    computeCovarianceMatrix (*cloud, xyz_centroid, covariance_matrix);


    int i;
    for(i=0; i<3; i++)
        std::cout << covariance_matrix(i,0) << "," << covariance_matrix(i,1) << "," <<covariance_matrix(i,2) << std::endl;

     std::cout <<""<< std::endl;

    /*
        0.710046,-0.234843,0.0704933
        -0.234843,0.68695,-0.220504
        0.0704933,-0.220504,0.195448
    */

    
  pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> ne;
  ne.setInputCloud (cloud);

  // Create an empty kdtree representation, and pass it to the normal estimation object.
  // Its content will be filled inside the object, based on the given input dataset (as no other search surface is given).
  pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ> ());
  ne.setSearchMethod (tree);

  // Output datasets
  pcl::PointCloud<pcl::Normal>::Ptr cloud_normals (new pcl::PointCloud<pcl::Normal>);

  // Use all neighbors in a sphere of radius 3cm
  ne.setRadiusSearch (0.03);

  // Compute the features
  ne.compute (*cloud_normals);


  pcl::visualization::PCLVisualizer viewer("PCL Viewer");

  
  //pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb(cloud);

  viewer.setBackgroundColor (0.0, 0.0, 0.5);

  pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> single_color(cloud, 0, 255, 0);
  viewer.addPointCloud<pcl::PointXYZ> (cloud, single_color, "sample cloud");
  //viewer.addPointCloudNormals<pcl::PointXYZ,pcl::Normal>(cloud, cloud_normals);

  viewer.addPointCloudNormals<pcl::PointXYZ,pcl::Normal>(cloud, cloud_normals,  1, 0.01, "normals1", 0);

  while (!viewer.wasStopped ())
  {
    viewer.spinOnce ();
  }

}


