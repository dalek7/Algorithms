#include <pcl/io/openni_grabber.h>
 #include <pcl/visualization/cloud_viewer.h>
#include <pcl/filters/voxel_grid.h>

#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/features/normal_3d.h>

#include <pcl/sample_consensus/method_types.h>
#include <pcl/sample_consensus/model_types.h>
#include <pcl/segmentation/sac_segmentation.h>

#include "pcproc.hpp"

#define    DATA_LEN    307200*6
#define    HEADER_LEN    4
HANDLE		hMemMap;
float*		lpMapping;

void InitSharedMemory();

class SimpleOpenNIViewer
{
public:
	SimpleOpenNIViewer () : viewer ("PCL OpenNI Viewer") 
	{
		bVoxelGrid = true;	

		leafsz = 0.025f;

	}

	bool bVoxelGrid;
	float leafsz;



	void keyboard_callback (const pcl::visualization::KeyboardEvent& event, void* cookie);
	void proc_key(unsigned char k);

	void mouse_callback (const pcl::visualization::MouseEvent& mouse_event, void* cookie)
    {
      string* message = (string*) cookie;
      if (mouse_event.getType() == pcl::visualization::MouseEvent::MouseButtonPress && mouse_event.getButton() == pcl::visualization::MouseEvent::LeftButton)
      {
        cout << (*message) << " :: " << mouse_event.getX () << " , " << mouse_event.getY () << endl;
      }
    }



     void cloud_cb_ (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr &cloud)
     {
		PCProc<pcl::PointXYZRGBA> pc1;
	
		pcl::PointCloud<pcl::PointXYZRGBA>::Ptr cloud_filtered (new pcl::PointCloud<pcl::PointXYZRGBA>);
		pcl::PointCloud<pcl::PointXYZRGBA>::Ptr output1 (new pcl::PointCloud<pcl::PointXYZRGBA>);
		


		
		
		
		
		if(bVoxelGrid)
		{
			pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr inputc = cloud;//.makeShared();
			pc1.downSampling(inputc,output1 , leafsz,leafsz,leafsz);

		}
		else
		{
			output1 = cloud->makeShared();
		}

		///////////////////////////////////////
		// passthrough

		pcl::PointCloud<pcl::PointXYZRGBA>::Ptr output2 (new pcl::PointCloud<pcl::PointXYZRGBA>);

		pc1.PassThroughZ(output1, output2, 1, 3);
		cloud_filtered = output2;





		
		///////////////////////////////////////
		// normal display

		
		pcl::NormalEstimation<pcl::PointXYZRGBA, pcl::Normal> ne;
		ne.setInputCloud (output2);


		// Create an empty kdtree representation, and pass it to the normal estimation object.
		// Its content will be filled inside the object, based on the given input dataset (as no other search surface is given).
		pcl::search::KdTree<pcl::PointXYZRGBA>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZRGBA> ());
		ne.setSearchMethod (tree);

		// Output datasets
		pcl::PointCloud<pcl::Normal>::Ptr cloud_normals (new pcl::PointCloud<pcl::Normal>);

		// Use all neighbors in a sphere of radius 3cm
		ne.setRadiusSearch (0.03);

		// Compute the features
		ne.compute (*cloud_normals);

	
		
		//viewer.addPointCloudNormals<pcl::PointXYZ,pcl::Normal>(cloud, cloud_normals,  1, 0.01, "normals1", 0);




		int nf = cloud_filtered->size();

		int n = cloud->size();
		lpMapping[0] = n;
		lpMapping[1] = nf;

		lpMapping[2] = bVoxelGrid;
		lpMapping[3] = leafsz;

;


		int i;

		for(i=0; i<nf; i++)//DATA_LEN/6
		{
			float x = cloud_filtered->points[i].x;
			lpMapping[HEADER_LEN + 6*i +0] = cloud_filtered->points[i].x;
			lpMapping[HEADER_LEN + 6*i +1] = cloud_filtered->points[i].y;
			lpMapping[HEADER_LEN + 6*i +2] = cloud_filtered->points[i].z;

			lpMapping[HEADER_LEN + 6*i +3] = cloud_filtered->points[i].r;
			lpMapping[HEADER_LEN + 6*i +4] = cloud_filtered->points[i].g;
			lpMapping[HEADER_LEN + 6*i +5] = cloud_filtered->points[i].b;


		}

		//viewer.addPointCloud<pcl::PointXYZ> (cloud,  "sample cloud");

       if (!viewer.wasStopped())
         {
			 
			 viewer.showCloud (cloud_filtered);
			 
	   }
     }

     void run ()
     {
       pcl::Grabber* interface1 = new pcl::OpenNIGrabber();

	   string keyMsg3D("Key event for PCL Visualizer");
	   viewer.registerKeyboardCallback(&SimpleOpenNIViewer::keyboard_callback, *this, (void*)(&keyMsg3D));

	   string mouseMsg3D("Mouse coordinates in PCL Visualizer");
	   viewer.registerMouseCallback (&SimpleOpenNIViewer::mouse_callback, *this, (void*)(&mouseMsg3D));    

       boost::function<void (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr&)> f =
         boost::bind (&SimpleOpenNIViewer::cloud_cb_, this, _1);

       interface1->registerCallback (f);

       interface1->start ();

       while (!viewer.wasStopped())
       {
         boost::this_thread::sleep (boost::posix_time::seconds (1));
       }

       interface1->stop ();
     }

     pcl::visualization::CloudViewer viewer;
	 //pcl::visualization::PCLVisualizer viewer;//("PCL Viewer");
 };

void SimpleOpenNIViewer::proc_key(unsigned char k)
{

	if(k=='1')
	{
		//cout << "1" << endl;

		bVoxelGrid ^= 1;
		
		cout << "bVoxelGrid: " << bVoxelGrid<< endl;
	}

	else if (k==91)	// '['
	{
		leafsz -= 0.01;
		if(leafsz <0.01) leafsz = 0.01;

		cout << "leafsz for voxel grid: " << leafsz<< endl;

	}

	
	else if (k==93)	// ']'
	{
		leafsz += 0.01;
		if(leafsz >0.5) leafsz = 0.5;

		cout << "leafsz for voxel grid: " << leafsz<< endl;

	}

}
void SimpleOpenNIViewer::keyboard_callback (const pcl::visualization::KeyboardEvent& event, void* cookie)
{

	unsigned char key = 0;
	

	string* message = (string*)cookie;
	cout << (*message) << " :: ";
	if (event.getKeyCode())
	{
		key = event.getKeyCode();
		//cout << "the key \'" << event.getKeyCode() << "\' (" << (int)event.getKeyCode() << ") was";
	}
	else
		;//cout << "the special key \'" << event.getKeySym() << "\' was";


	if (event.keyDown())
		;//cout << " pressed" << endl;
	else
	{
		if(key )
		{
			proc_key(key);

			//cout << " released" << endl;
			
		}

		
		

		
	}
}

 int main ()
 {
	InitSharedMemory();
	SimpleOpenNIViewer v;
   
	//pcl::gpu::printShortCudaDeviceInfo
   
	v.run ();
	return 0;
 }

 void InitSharedMemory()
 {
	 
	 hMemMap = CreateFileMapping((HANDLE)0xFFFFFFFF,
                                NULL,
                                PAGE_READWRITE,
                                0,
                                HEADER_LEN+DATA_LEN*sizeof(float),//HEADER_LEN+
                                "MemShare1");


	if(!hMemMap)
		printf("Error 1");
	else
	{
		printf("OK...1");
	}


	lpMapping = (float*) MapViewOfFile(hMemMap,
                    FILE_MAP_ALL_ACCESS,
                    0,
                    0,
                    0);

	if(!lpMapping)
		printf("Error 2");
	else
	{
		printf("OK...2");
	}
 }