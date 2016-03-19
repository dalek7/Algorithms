#ifndef PCPROC_H
#define PCPROC_H



// PCL
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/kdtree/kdtree.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/ModelCoefficients.h>

#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

#include <pcl/features/normal_3d.h>

#include <pcl/filters/passthrough.h>

#include <vector>

#include "common.h"

using namespace std;


typedef struct {
    double left, right, top, bottom, ztop, zbottom;
    double margin;
} PC_TYPE_WS;

uint32_t clr[8] = { (uint32_t)255 << 16 | (uint32_t)0 << 8 | (uint32_t)0,
                    (uint32_t)0 << 16 | (uint32_t)255 << 8 | (uint32_t)0,
                    (uint32_t)0 << 16 | (uint32_t)0 << 8 | (uint32_t)255,
                    (uint32_t)255 << 16 | (uint32_t)0 << 8 | (uint32_t)0,
                    (uint32_t)255 << 16 | (uint32_t)255 << 8 | (uint32_t)0,
                    (uint32_t)255 << 16 | (uint32_t)0 << 8 | (uint32_t)255,
                    (uint32_t)0 << 16 | (uint32_t)255 << 8 | (uint32_t)255,
                    (uint32_t)255 << 16 | (uint32_t)255 << 8 | (uint32_t)255

                  };


template <typename T>
class PCProc
{
public:
    PCProc();

public:

    typedef pcl::PointCloud<T> Cloud;
    typedef typename Cloud::Ptr CloudPtr;
    typedef typename Cloud::ConstPtr CloudConstPtr;

    typedef std::vector<CloudPtr> VecCloud;


public:

    bool downSampling(CloudConstPtr &cloud_in, CloudPtr &cloud_out, double leaf_x, double leaf_y, double leaf_z);
	bool PassThroughZ(CloudPtr &cloud_in, CloudPtr &cloud_out, float limit_min=0.0, float limit_max = 2.0);
    bool cut(CloudPtr &cloud_in, CloudPtr &cloud_out, PC_TYPE_WS ws);

    bool extractPlane(CloudPtr &cloud_in, CloudPtr &cloud_out, VecCloud &clouds_plane, int nPlane, float distancethreshold_/*=0.02*/);

    bool extractPlane(CloudPtr &cloud_in, CloudPtr &cloud_out, VecCloud &clouds_plane, int nPlane);

    //Extract the planar inliers from the input cloud
    bool extractPlanarInliers(CloudPtr &cloud_in, CloudPtr &cloud_out, float v_ratio=0.5);


    int EuclideanClusterExtraction(CloudPtr &cloud_in, CloudPtr &cloud_out, int minClusterSize=30, int maxClusterSize=25000, float clusterTolerance=0.02);//0.02 for 2cm
    //bool downSampling(CloudConstPtr &cloud_in, CloudPtr &cloud_out, double leaf_x, double leaf_y, double leaf_z);

    int FindSphereInEuclideanClusters(CloudPtr &cloud_in, CloudPtr &cloud_out,CloudPtr &cloud_out_found_target, int minClusterSize=30, int maxClusterSize=25000, float clusterTolerance=0.02);//0.02 for 2cm

    int FindTemplateInEuclideanClusters(CloudPtr &cloud_in, CloudPtr &cloud_in_template, CloudPtr &cloud_out,CloudPtr &cloud_out_found_target, int minClusterSize=30, int maxClusterSize=25000, float clusterTolerance=0.02);//0.02 for 2cm



private:



};

#endif // PCTRACKING_H
