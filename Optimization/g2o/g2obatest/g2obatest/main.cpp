//
//  main.cpp
//  g2obatest
//
//  Created by Seung-Chan Kim on 1/11/17.
//  based on https://github.com/gaoxiang12/g2o_ba_example
//  http://nimbro.net/OP/Doc/html/Localization_8hpp_source.html

#include <iostream>

//#include <Eigen/Core>
//#include <Eigen/StdVector>

// opencv
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>

// g2o
#include <g2o/core/sparse_optimizer.h>
#include <g2o/core/block_solver.h>
#include <g2o/core/robust_kernel.h>
#include <g2o/core/robust_kernel_impl.h>
#include <g2o/core/optimization_algorithm_levenberg.h>
#include <g2o/solvers/cholmod/linear_solver_cholmod.h>
#include <g2o/solvers/csparse/linear_solver_csparse.h>
#include <g2o/types/slam3d/se3quat.h>
#include <g2o/types/sba/types_six_dof_expmap.h>

using namespace std;
using namespace g2o;
using namespace cv;

int     findCorrespondingPoints( const cv::Mat& img1, const cv::Mat& img2, vector<cv::Point2f>& points1, vector<cv::Point2f>& points2 );

double cx = 325.5;
double cy = 253.5;
double fx = 518.0;
double fy = 519.0;

int main(int argc, const char * argv[]) {
    
    cv::Mat img1;
    cv::Mat img2;
    
    if (argc != 3)
    {
        img1 =cv::imread("../../../data/set1/1.png");
        img2 =cv::imread("../../../data/set1/2.png");
    }
    else
    {
        img1 = cv::imread( argv[1] );
        img2 = cv::imread( argv[2] );
    }
    cout << "loaded " << img1.size().width << " X " << img1.size().height << " X " << img1.channels() << endl;
    
    
    vector<cv::Point2f> pts1, pts2;
    if ( findCorrespondingPoints( img1, img2, pts1, pts2 ) == false )
    {
        cout<<"too few feature matches！ # of matches = "<< pts1.size() << endl;
        return 0;
    }
    cout<<"# of matches = "<< pts1.size() << endl;
    
    g2o::SparseOptimizer    optimizer;
    
#if 1
    // create the linear solver
    g2o::BlockSolver_6_3::LinearSolverType* linearSolver = new  g2o::LinearSolverCholmod<g2o::BlockSolver_6_3::PoseMatrixType> ();
    
    // create the block solver on the top of the linear solver
    // solver for BA/3D SLAM
    // typedef BlockSolver< BlockSolverTraits<6, 3> > BlockSolver_6_3;
    g2o::BlockSolver_6_3* block_solver = new g2o::BlockSolver_6_3( linearSolver );
    
#else
    // create the linear solver
    BlockSolverX::LinearSolverType * linearSolver;
    linearSolver = new LinearSolverCSparse<BlockSolverX::PoseMatrixType>();
    
    // create the block solver on the top of the linear solver
    // variable size solver
    // typedef BlockSolver< BlockSolverTraits<Eigen::Dynamic, Eigen::Dynamic> > BlockSolverX;
   
    BlockSolverX* block_solver;
    block_solver = new BlockSolverX(linearSolver);

#endif
    
    //create the algorithm to carry out the optimization
    g2o::OptimizationAlgorithmLevenberg* algorithm = new g2o::OptimizationAlgorithmLevenberg( block_solver );
    
    optimizer.setAlgorithm( algorithm );
    
    
    for ( int i=0; i<2; i++ )
    {
        // SE3 Vertex parameterized internally with a transformation matrix and externally with its exponential map
        g2o::VertexSE3Expmap* v = new g2o::VertexSE3Expmap();
        v->setId(i);
        if ( i == 0)
            v->setFixed( true );
        
        v->setEstimate( g2o::SE3Quat() );
        optimizer.addVertex( v );
    }
    cout << g2o::SE3Quat()  << endl;
    for ( size_t i=0; i<pts1.size(); i++ )
    {
        g2o::VertexSBAPointXYZ* v = new g2o::VertexSBAPointXYZ();
        v->setId( 2 + i );
        
        double z = 1;
        double x = ( pts1[i].x - cx ) * z / fx;
        double y = ( pts1[i].y - cy ) * z / fy;
        v->setMarginalized(true);
        v->setEstimate( Eigen::Vector3d(x,y,z) );
        optimizer.addVertex( v );
    }
    
    g2o::CameraParameters* camera = new g2o::CameraParameters( fx, Eigen::Vector2d(cx, cy), 0 );
    camera->setId(0);
    optimizer.addParameter( camera );
    
    // First frame
    vector<g2o::EdgeProjectXYZ2UV*> edges;
    for ( size_t i=0; i<pts1.size(); i++ )
    {
        g2o::EdgeProjectXYZ2UV*  edge = new g2o::EdgeProjectXYZ2UV();
        edge->setVertex( 0, dynamic_cast<g2o::VertexSBAPointXYZ*>   (optimizer.vertex(i+2)) );
        edge->setVertex( 1, dynamic_cast<g2o::VertexSE3Expmap*>     (optimizer.vertex(0)) );
        edge->setMeasurement( Eigen::Vector2d(pts1[i].x, pts1[i].y ) );
        edge->setInformation( Eigen::Matrix2d::Identity() );
        edge->setParameterId(0, 0);
        
        edge->setRobustKernel( new g2o::RobustKernelHuber() );
        optimizer.addEdge( edge );
        edges.push_back(edge);
    }

    // Second frame
    for ( size_t i=0; i<pts2.size(); i++ )
    {
        g2o::EdgeProjectXYZ2UV*  edge = new g2o::EdgeProjectXYZ2UV();
        edge->setVertex( 0, dynamic_cast<g2o::VertexSBAPointXYZ*>   (optimizer.vertex(i+2)) );
        edge->setVertex( 1, dynamic_cast<g2o::VertexSE3Expmap*>     (optimizer.vertex(1)) );
        edge->setMeasurement( Eigen::Vector2d(pts2[i].x, pts2[i].y ) );
        edge->setInformation( Eigen::Matrix2d::Identity() );
        edge->setParameterId(0,0);
        
        edge->setRobustKernel( new g2o::RobustKernelHuber() );
        optimizer.addEdge( edge );
        edges.push_back(edge);
    }
    
    optimizer.setVerbose(true);
    optimizer.initializeOptimization();
    optimizer.optimize(10);
    
    cout << "Optimization done.." << endl;
    
    g2o::VertexSE3Expmap* v0 = dynamic_cast<g2o::VertexSE3Expmap*>( optimizer.vertex(0) );
    Eigen::Isometry3d pose0 = v0->estimate();
    cout<<"Pose (fixed) ="<<endl<<pose0.matrix()<<endl;
    
    g2o::VertexSE3Expmap* v = dynamic_cast<g2o::VertexSE3Expmap*>( optimizer.vertex(1) );
    Eigen::Isometry3d pose = v->estimate();
    cout<<"Pose="<<endl<<pose.matrix()<<endl;
    
    if(0)
    for ( size_t i=0; i<pts1.size(); i++ )
    {
        g2o::VertexSBAPointXYZ* v = dynamic_cast<g2o::VertexSBAPointXYZ*> (optimizer.vertex(i+2));
        cout<<"vertex id "<<i+2<<", pos = ";
        Eigen::Vector3d pos = v->estimate();
        cout<<pos(0)<<","<<pos(1)<<","<<pos(2)<<endl;
    }
    
    int inliers = 0;
    for ( auto e:edges )
    {
        e->computeError();
        
        if ( e->chi2() > 1 )
        {
            cout<<"error = "<<e->chi2()<<endl;
        }
        else
        {
            inliers++;
        }
    }
    
    cout<<"inliers in total points: "<<inliers<<"/"<<pts1.size()+pts2.size()<<endl;
    optimizer.save("ba.g2o");
    
    imshow("img1", img1);
    imshow("img2", img2);
    cv::waitKey(-1);
    
    std::cout << "Done !\n";
    return 0;
}


int     findCorrespondingPoints( const cv::Mat& img1, const cv::Mat& img2, vector<cv::Point2f>& points1, vector<cv::Point2f>& points2 )
{
    cv::Ptr<cv::FeatureDetector>		detector;
    cv::Ptr<cv::DescriptorExtractor>	extractor;
    
    detector = cv::ORB::create();
    extractor = cv::ORB::create();
    
    vector<cv::KeyPoint> kp1, kp2;
    cv::Mat desc1, desc2;
    
    detector->detect(img1, kp1);
    detector->detect(img2, kp2);
    
    extractor->compute(img1,kp1,desc1);
    extractor->compute(img2,kp2,desc2);
    
    //cv::ORB orb;
    
    cout<<"# of kp= "<<kp1.size()<<" & "<<kp2.size()<<endl;
    
    cv::Ptr<cv::DescriptorMatcher>  matcher = cv::DescriptorMatcher::create( "BruteForce-Hamming");
    
    double knn_match_ratio=0.8;
    vector< vector<cv::DMatch> > matches_knn;
    matcher->knnMatch( desc1, desc2, matches_knn, 2 );
    vector< cv::DMatch > matches;
    for ( size_t i=0; i<matches_knn.size(); i++ )
    {
        if (matches_knn[i][0].distance < knn_match_ratio * matches_knn[i][1].distance )
            matches.push_back( matches_knn[i][0] );
    }
    
    if (matches.size() <= 20)
        return false;
    
    for ( auto m:matches )
    {
        points1.push_back( kp1[m.queryIdx].pt );
        points2.push_back( kp2[m.trainIdx].pt );
    }
    
    
    
    return true;
}




