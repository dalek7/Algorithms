#include "pcproc.h"
//#include "ddRansac.hpp"
#include <pcl/common/pca.h>

template<typename T>
PCProc<T>::PCProc()
{
}



template<typename T>
bool PCProc<T>::downSampling(CloudConstPtr &cloud_in, CloudPtr &cloud_out, double leaf_x, double leaf_y, double leaf_z)
{
    //    std::cout << "Down sampling" << std::endl;

    pcl::VoxelGrid<T> vg;
    //    vg.setInputCloud(cloud_preprocessed);

    vg.setInputCloud(cloud_in);
    //  setInputCloud (const PointCloudConstPtr &cloud) { input_ = cloud; }
    vg.setLeafSize(leaf_x, leaf_y, leaf_z); // down sampling using a leaf size of 1cm
    vg.filter(*cloud_out);


    return 1;
}


template<typename T>
bool PCProc<T>::PassThroughZ(CloudPtr &cloud_in, CloudPtr &cloud_out, float limit_min, float limit_max)
{


    cloud_out.reset (new Cloud);
   

	
	pcl::PassThrough<T> pass;
    pass.setInputCloud (cloud_in);

    pass.setFilterFieldName ("z");
    pass.setFilterLimits (limit_min, limit_max);

    pass.filter (*cloud_out);


    return 1;
}



template<typename T>
bool PCProc<T>::cut(CloudPtr &cloud_in, CloudPtr &cloud_out, PC_TYPE_WS ws)
{
    cloud_out.reset (new Cloud);
    //    std::cout << "Workspace cutting" << std::endl;
    for(int i=0;i<cloud_in->points.size();i++){
        T temp_point = cloud_in->points[i];
        // cut off
        if(temp_point.x<ws.right && temp_point.x>ws.left && temp_point.y<ws.top && temp_point.y>ws.bottom && temp_point.z>ws.zbottom && temp_point.z<ws.ztop)
                cloud_out->points.push_back(temp_point);
    }
    return 1;
}

template<typename T>
bool PCProc<T>::extractPlane(CloudPtr &cloud_in, CloudPtr &cloud_out, VecCloud &clouds_plane, int nPlane, float distancethreshold_)
{

    cloud_out.reset (new Cloud);
    *cloud_out = *cloud_in;


    pcl::SACSegmentation<T> seg;
    pcl::PointIndices::Ptr inliers (new pcl::PointIndices);
    pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients);

    seg.setOptimizeCoefficients (true);
    seg.setModelType (pcl::SACMODEL_PLANE);
    seg.setMethodType (pcl::SAC_RANSAC);
    seg.setMaxIterations (100);
    seg.setDistanceThreshold (distancethreshold_);

    // plane segmentation
    for(int i=0;i<nPlane;i++)
    {

        // Segment the largest planar component from the remaining cloud
        seg.setInputCloud(cloud_out);
        seg.segment (*inliers, *coefficients); //*
        if (inliers->indices.size () == 0)
        {
            std::cout << "Could not estimate a planar model for the given dataset." << std::endl;
            break;
        }


        // Extract the planar inliers from the input cloud
        pcl::ExtractIndices<T> extract;
        extract.setInputCloud (cloud_out);
        extract.setIndices (inliers);
        extract.setNegative (false);


        // Write the planar inliers to disk
        CloudPtr cloud_plane;
        cloud_plane.reset(new Cloud);
        extract.filter (*cloud_plane); //*
        clouds_plane.push_back(cloud_plane);

        // Remove the planar inliers, extract the rest
        extract.setNegative (true);
        extract.filter (*cloud_out); //*



    }



    return 1;
}


template<typename T>
bool PCProc<T>::extractPlane(CloudPtr &cloud_in, CloudPtr &cloud_out, VecCloud &clouds_plane, int nPlane)
{
    cloud_out.reset (new Cloud);
    *cloud_out = *cloud_in;
    //    std::cout << "Plane Extraction" << std::endl;
    // Create the segmentation object for the planar model and set all the parameters
    pcl::SACSegmentation<T> seg;
    pcl::PointIndices::Ptr inliers (new pcl::PointIndices);
    pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients);
    //    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_plane (new pcl::PointCloud<pcl::PointXYZ> ());
    seg.setOptimizeCoefficients (true);
    seg.setModelType (pcl::SACMODEL_PLANE);
    seg.setMethodType (pcl::SAC_RANSAC);
    seg.setMaxIterations (100);
    seg.setDistanceThreshold (0.02);

    // plane segmentation
    for(int i=0;i<nPlane;i++)
    {
        // Segment the largest planar component from the remaining cloud
        seg.setInputCloud(cloud_out);
        seg.segment (*inliers, *coefficients); //*
        if (inliers->indices.size () == 0)
        {
            std::cout << "Could not estimate a planar model for the given dataset." << std::endl;
            break;
        }

        // Extract the planar inliers from the input cloud
        pcl::ExtractIndices<T> extract;
        extract.setInputCloud (cloud_out);
        extract.setIndices (inliers);
        extract.setNegative (false);

        // Write the planar inliers to disk
        CloudPtr cloud_plane;
        cloud_plane.reset(new Cloud);
        extract.filter (*cloud_plane); //*
        clouds_plane.push_back(cloud_plane);
        //      std::cout << "PointCloud representing the planar component: " << cloud_plane->points.size () << " data points." << std::endl;

        // Remove the planar inliers, extract the rest
        extract.setNegative (true);
        extract.filter (*cloud_out); //*
    }
//    cloud_out = cloud_in;
    return 1;
}


template<typename T>
bool PCProc<T>::extractPlanarInliers(CloudPtr &cloud_in, CloudPtr &cloud_out, float v_ratio)
{
    cloud_out.reset (new Cloud);
    *cloud_out = *cloud_in;


    CloudPtr cloud_tmp;
    cloud_tmp.reset(new Cloud);


    // Create the segmentation object for the planar model and set all the parameters
    pcl::SACSegmentation<T> seg;
    pcl::PointIndices::Ptr inliers (new pcl::PointIndices);
    pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients);

    CloudPtr cloud_plane;
    cloud_plane.reset(new Cloud);


    seg.setOptimizeCoefficients (true);
    seg.setModelType (pcl::SACMODEL_PLANE);
    seg.setMethodType (pcl::SAC_RANSAC);
    seg.setMaxIterations (100);
    seg.setDistanceThreshold (0.02);


    int i=0;
    int nr_points = (int) cloud_in->points.size ();

    while (cloud_out->points.size () > v_ratio * nr_points)
    {

        // Segment the largest planar component from the remaining cloud
        seg.setInputCloud (cloud_out);
        seg.segment (*inliers, *coefficients);
        if (inliers->indices.size () == 0)
        {
          //std::cout << "Could not estimate a planar model for the given dataset." << std::endl;
          break;
        }

        // Extract the planar inliers from the input cloud
        pcl::ExtractIndices<T> extract;
        extract.setInputCloud(cloud_out);
        extract.setIndices(inliers);
        extract.setNegative(false);


        // Get the points associated with the planar surface
        extract.filter (*cloud_plane);
        //std::cout << "PointCloud representing the planar component: " << cloud_plane->points.size () << " data points." << std::endl;

        // Remove the planar inliers, extract the rest
        extract.setNegative (true);
        extract.filter(*cloud_tmp);
        *cloud_out = *cloud_tmp;

    }



    return 0;
}

/*
// NEED TO IMPLEMENT
template<typename T>
int PCProc<T>::FindTemplateInEuclideanClusters(CloudPtr &cloud_in, CloudPtr &cloud_in_template,CloudPtr &cloud_out, CloudPtr &cloud_out_found_target, int minClusterSize, int maxClusterSize, float clusterTolerance)
{

    cloud_out.reset (new Cloud);

    // Creating the KdTree object for the search method of the extraction
    pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZRGB>);
    tree->setInputCloud(cloud_in);

    std::vector<pcl::PointIndices> cluster_indices;
    pcl::EuclideanClusterExtraction<pcl::PointXYZRGB> ec;
    ec.setClusterTolerance (clusterTolerance); // 2cm
    ec.setMinClusterSize (minClusterSize);//100
    ec.setMaxClusterSize (maxClusterSize);
    ec.setSearchMethod (tree);
    ec.setInputCloud (cloud_in);
    ec.extract (cluster_indices);


    int i=0;

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_chk (new pcl::PointCloud<pcl::PointXYZ>);
    ddRansac<pcl::PointXYZ> rsc1;
    int nMaxInliers=0;
    int maxID = -1;
    std::vector<int> inliers;
    for (std::vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin (); it != cluster_indices.end (); ++it)
    {

         pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_cluster (new pcl::PointCloud<pcl::PointXYZRGB>);
         for (std::vector<int>::const_iterator pit = it->indices.begin (); pit != it->indices.end (); pit++)
         {
             pcl::PointXYZRGB pf = cloud_in->points[*pit];

             int32_t rgb = clr[i%8];
             pf.rgb = *(float*)(&rgb);

             cloud_cluster->points.push_back(pf);

         }

         cloud_cluster->width = cloud_cluster->points.size ();
         cloud_cluster->height = 1;
         cloud_cluster->is_dense = true;

         // Check whether the cloud fits with the given model

         cloud_chk->points.resize(cloud_cluster->size());
         for (size_t j = 0; j < cloud_cluster->points.size(); j++)
         {
             cloud_chk->points[j].x = cloud_cluster->points[j].x;
             cloud_chk->points[j].y = cloud_cluster->points[j].y;
             cloud_chk->points[j].z = cloud_cluster->points[j].z;
         }

         pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud_in_c = cloud_chk;
         pcl::PointCloud<pcl::PointXYZ>::Ptr final (new pcl::PointCloud<pcl::PointXYZ>);

         std::vector<int> inliers1;
         int nInliers = rsc1.RANSACSphere(cloud_in_c, final,inliers1, 0.001);

         if(nInliers > nMaxInliers)
         {
             nMaxInliers = nInliers;
             maxID = i;
             //inliers = inliers1;
             inliers.swap(inliers1);


         }
         i++;
    }

    //cout << nMaxInliers <<std::endl;


    //pcl::copyPointCloud<T>(*cloud_in, inliers, *cloud_out);


    {
        *cloud_out = *cloud_in;

        int32_t rgb = clr[1];
        for (std::vector<int>::const_iterator pit = cluster_indices[maxID].indices.begin (); pit != cluster_indices[maxID].indices.end (); pit++)
        {

            cloud_out->points[*pit].rgb = *(float*)(&rgb);
        }
    }



    {

      //  pcl::copyPointCloud<T>(*cloud_in, inliers, *cloud_out);


    }


    pcl::copyPointCloud<T>(*cloud_in, inliers, *cloud_out_found_target);

    return i;   //# of cluster
}
*/


template<typename T>
int PCProc<T>::FindSphereInEuclideanClusters(CloudPtr &cloud_in, CloudPtr &cloud_out, CloudPtr &cloud_out_found_target, int minClusterSize, int maxClusterSize, float clusterTolerance)
{

    cloud_out.reset (new Cloud);

    // Creating the KdTree object for the search method of the extraction
    pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZRGB>);
    tree->setInputCloud(cloud_in);

    std::vector<pcl::PointIndices> cluster_indices;
    pcl::EuclideanClusterExtraction<pcl::PointXYZRGB> ec;
    ec.setClusterTolerance (clusterTolerance); // 2cm
    ec.setMinClusterSize (minClusterSize);//100
    ec.setMaxClusterSize (maxClusterSize);
    ec.setSearchMethod (tree);
    ec.setInputCloud (cloud_in);
    ec.extract (cluster_indices);

    int i=0;

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_chk (new pcl::PointCloud<pcl::PointXYZ>);
    ddRansac<pcl::PointXYZ> rsc1;
    int nMaxInliers=0;
    int maxID = -1;
    std::vector<int> inliers;
    for (std::vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin (); it != cluster_indices.end (); ++it)
    {

         pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_cluster (new pcl::PointCloud<pcl::PointXYZRGB>);
         for (std::vector<int>::const_iterator pit = it->indices.begin (); pit != it->indices.end (); pit++)
         {
             pcl::PointXYZRGB pf = cloud_in->points[*pit];

             int32_t rgb = clr[i%8];
             pf.rgb = *(float*)(&rgb);

             cloud_cluster->points.push_back(pf);

         }

         cloud_cluster->width = cloud_cluster->points.size ();
         cloud_cluster->height = 1;
         cloud_cluster->is_dense = true;

         // Check whether the cloud fits with the given model

         cloud_chk->points.resize(cloud_cluster->size());
         for (size_t j = 0; j < cloud_cluster->points.size(); j++)
         {
             cloud_chk->points[j].x = cloud_cluster->points[j].x;
             cloud_chk->points[j].y = cloud_cluster->points[j].y;
             cloud_chk->points[j].z = cloud_cluster->points[j].z;
         }


         pcl::PointCloud<pcl::PointXYZ>::ConstPtr cloud_in_c = cloud_chk;
         pcl::PointCloud<pcl::PointXYZ>::Ptr final (new pcl::PointCloud<pcl::PointXYZ>);


         pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_inliers (new pcl::PointCloud<pcl::PointXYZ>);

         //pcl::PointCloud<pcl::PointXYZRGB>::Ptr final_rgb (new pcl::PointCloud<pcl::PointXYZRGB>);


         std::vector<int> inliers1;
         int nInliers = rsc1.RANSACSphere(cloud_in_c, final,inliers1, 0.001);

         if(nInliers > nMaxInliers)
         {
             nMaxInliers = nInliers;
             maxID = i;

             pcl::copyPointCloud< pcl::PointXYZ, pcl::PointXYZRGB>(*cloud_in_c, inliers1, *cloud_out_found_target);


             //inliers = inliers1;
             inliers.swap(inliers1);
             //cloud_out_found_target = final;


/*
             if(0)
             if(dispOnlyDetected==1)
             *cloud_out = *cloud_cluster;
*/



         }
         i++;
    }

    //cout << nMaxInliers <<std::endl;



    //cloud_out_found_target.reset (new Cloud);
  //cloud_out_found_target->points.resize(cluster_indices[maxID].indices.size());



    {
        *cloud_out = *cloud_in;

        int32_t rgb = clr[1];
        int k = 0;
        for (std::vector<int>::const_iterator pit = cluster_indices[maxID].indices.begin (); pit != cluster_indices[maxID].indices.end (); pit++)
        {

            cloud_out->points[*pit].rgb = *(float*)(&rgb);


//cloud_out->points[*pit]

            //cloud_out_found_target->points[k].x = cloud_out->points[*pit].x;
            //cloud_out_found_target->points[k].y = cloud_out->points[*pit].y;
            //cloud_out_found_target->points[k].z = cloud_out->points[*pit].z;

/*
            pcl::PointXYZRGB pf = cloud_out->points[*pit];

            int32_t rgb = clr[0];
            pf.rgb = *(float*)(&rgb);

            cloud_out_found_target->points.push_back(pf);


*/
        }


        /*
        cloud_out_found_target->width = cloud_out_found_target->points.size ();
        cloud_out_found_target->height = 1;
        pcl::copyPointCloud<T>(*cloud_in, inliers, *cloud_out_found_target);
        */

        //



    }


     //pcl::copyPointCloud<T>(*cloud_in, inliers, *cloud_out);


    return i;   //# of cluster
}

template<typename T>
int PCProc<T>::EuclideanClusterExtraction(CloudPtr &cloud_in, CloudPtr &cloud_out, int minClusterSize, int maxClusterSize, float clusterTolerance)
{

    cloud_out.reset (new Cloud);





    // Creating the KdTree object for the search method of the extraction
    pcl::search::KdTree<pcl::PointXYZRGB>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZRGB>);
    tree->setInputCloud(cloud_in);

    std::vector<pcl::PointIndices> cluster_indices;
    pcl::EuclideanClusterExtraction<pcl::PointXYZRGB> ec;
    ec.setClusterTolerance (clusterTolerance); // 2cm
    ec.setMinClusterSize (minClusterSize);//100
    ec.setMaxClusterSize (maxClusterSize);
    ec.setSearchMethod (tree);
    ec.setInputCloud (cloud_in);
    ec.extract (cluster_indices);


    int i=0;



    for (std::vector<pcl::PointIndices>::const_iterator it = cluster_indices.begin (); it != cluster_indices.end (); ++it)
    {

         pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_cluster (new pcl::PointCloud<pcl::PointXYZRGB>);
         for (std::vector<int>::const_iterator pit = it->indices.begin (); pit != it->indices.end (); pit++)
         {
             pcl::PointXYZRGB pf = cloud_in->points[*pit];

             int32_t rgb = clr[i%8];
             pf.rgb = *(float*)(&rgb);

             cloud_cluster->points.push_back(pf);



         }

         cloud_cluster->width = cloud_cluster->points.size ();
         cloud_cluster->height = 1;
         cloud_cluster->is_dense = true;

         *cloud_out = *cloud_out + *cloud_cluster;



         i++;

    }

    return i;   //# of cluster




}


/*
template<typename T>
bool PCProc<T>::downSampling(CloudConstPtr &cloud_in, CloudPtr &cloud_out, double leaf_x, double leaf_y, double leaf_z)
{
    //    std::cout << "Down sampling" << std::endl;
    // down sampling
    pcl::VoxelGrid<T> vg;
    //    vg.setInputCloud(cloud_preprocessed);
    vg.setInputCloud(cloud_in);
    vg.setLeafSize(leaf_x, leaf_y, leaf_z); // down sampling using a leaf size of 1cm
    vg.filter(*cloud_out);
    return 1;
}

*/
