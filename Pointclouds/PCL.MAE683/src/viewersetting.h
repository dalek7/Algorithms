#include <pcl/ModelCoefficients.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>

//0.00440987,4.40987/0.0124525,-0.0287947,0.583038/
//0.0655697,0.616312,-0.341916/0.0457453,-0.820586,-0.569689/
//0.523599/640,512/66,52
inline void setView1(pcl::visualization::PCLVisualizer& viewer)
{

    viewer.camera_.clip[0] = 0.00393101;    viewer.camera_.clip[1] = 3.93101;    viewer.camera_.focal[0] = -0.022696;    viewer.camera_.focal[1] = 0.169112;    viewer.camera_.focal[2] = 0.356029;

    viewer.camera_.pos[0] = -0.0259827;    viewer.camera_.pos[1] = 0.428571;    viewer.camera_.pos[2] = -0.0275477;

    viewer.camera_.view[0] = -0.030215;    viewer.camera_.view[1] = -0.828045;    viewer.camera_.view[2] = -0.559847;

    viewer.camera_.fovy = 0.523599;    viewer.camera_.window_size[0] = 960;    viewer.camera_.window_size[1] = 520;    viewer.camera_.window_pos[0] = 0;    viewer.camera_.window_pos[1] = 0;

    viewer.updateCamera();

}

/*
 viewer.camera_.view[0] = 0;
 viewer.camera_.view[1] = 0;
 viewer.camera_.view[2] = 0;

  viewer.camera_.pos[0] = 0;
  viewer.camera_.pos[1] = 0;
  viewer.camera_.pos[2] = -2;

  viewer.camera_.focal[0] = 0;
  viewer.camera_.focal[1] = 0;
  viewer.camera_.focal[2] = 0;

  viewer.camera_.clip[0] = -10.01;
  viewer.camera_.clip[1] = 10.01;
  viewer.updateCamera();
*/

// for the discussions
// http://www.pcl-users.org/PCLVisualizer-viewer-camera-setting-td2968333.html
