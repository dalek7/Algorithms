// For testing FLANN lib in OpenCV 2
// Seung-Chan Kim


#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


void PrintMat(const cv::Mat& mat)
{
	int i,j;
	
	for( i = 0; i <mat.rows; i++)
	{
		for(j=0; j<mat.cols; j++)
		{
			printf("%.4f", mat.at<float>(mat.cols*i,j));
			if(j== mat.cols -1)
				printf("\n");
			else
				printf(",");
		}

		//printf("%.4f %.4f %.4f\n", mat.at<double>(3*i,1),mat.at<double>(3*i,2),mat.at<double>(3*i,3));
		
	}

}


int main( int argc, char** argv )
{


	int numData                = 5;
	int numQueries             = 2;
	int numDimensions    = 1;
	int k                      = 1;
	float Mean                 = 0.0f;
	float Variance             = 1.0f;

	
  // Create the data
	Mat features(numData,numDimensions,CV_32F);
	Mat query(numQueries,numDimensions,CV_32F);
	
	
	randu(features, Scalar::all(Mean), Scalar::all(Variance));
    randu(query, Scalar::all(Mean), Scalar::all(Variance));
       
       
       
	printf( "==features==\n" );
	PrintMat(features);
	
	
	printf( "\n");
	printf( "==query==\n");
	PrintMat(query);




	cv::flann::KDTreeIndexParams indexParams(5);
       
       
       
	// You can also use LinearIndex
	//cv::flann::LinearIndexParams indexParams;
	
	
	// Create the Index
	cv::flann::Index kdtree(features, indexParams, cvflann::FLANN_DIST_L2);        //cvflann::FLANN_DIST_L1   //FLANN_DIST_L2
	
	
	printf( "kdtree with FLANN_DIST_L2\n" );
    
    printf( "\n==Single Query==\n" );
    
	
	vector< float> singleQuery;
	vector< int> index;
	vector< float> dist;     




	int i;
	float vin = 0.0;
	// Searching for the Mean
	for(i = 0 ; i < numDimensions ;i++)
	{
		  singleQuery.push_back(vin);
		  printf( "singleQuery dim #%d = %.4f\n" , i, singleQuery[i]);
	}
	
	
	// Invoke the function
	kdtree.knnSearch(singleQuery, index, dist, 2, cv::flann::SearchParams(64));


	printf( "Index\tFeature\tDist\tL1\tL2\n" );
	for(i=0; i<2; i++)
	{
		   float feature = features.at<float>(index[i],0);
		   float L1             = fabs(vin -feature );
		   float L2             = L1*L1;
				 
		   //L1*L1  /2.0;;
		   //2 * (sqrt(1+ L1*L1 / 2)  -1);
	
	
		  printf( "%d\t%.4f\t%.4f\t%.4f\t%.4f\n" , index[i], feature, dist[i],       L1, L2);
		   //cout << "(index,dist):" << index[i] << ","<<feature << ",,,"<< dist[i]<<endl;
		  
	
	
	}



  //waitKey(0);

  return 0;
}

