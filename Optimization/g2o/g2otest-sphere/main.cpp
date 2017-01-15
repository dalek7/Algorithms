// g2o sphere
// based on https://github.com/RainerKuemmerle/g2o/blob/master/g2o/examples/sphere/create_sphere.cpp
// reference 1 :  https://malcolmmielle.wordpress.com/2016/06/20/g2o-optimization/
// reference 2 : http://fzheng.me/2016/03/15/g2o-demo/
// Created by Seung-Chan Kim on 12/29/16.


#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include <Eigen/Core>
#include <Eigen/StdVector>

#include "g2o/types/slam3d/vertex_se3.h"
#include "g2o/types/slam3d/edge_se3.h"
#include "g2o/stuff/sampler.h"
#include "g2o/stuff/command_args.h"
#include "g2o/core/factory.h"


#include "g2o/core/sparse_optimizer.h"
#include "g2o/core/block_solver.h"
#include "g2o/core/optimization_algorithm_gauss_newton.h"
#include "g2o/core/optimization_algorithm_levenberg.h"
#include "g2o/solvers/csparse/linear_solver_csparse.h"


using namespace std;
using namespace g2o;

int main(int argc, char** argv)
{
    // command line parsing
    int nodesPerLevel;
    int numLaps;
    bool randomSeed;
    double radius;
    std::vector<double> noiseTranslation;
    std::vector<double> noiseRotation;
    string outFilename;
    CommandArgs arg;
    arg.param("o", outFilename, "-", "output filename");
    arg.param("nodesPerLevel", nodesPerLevel, 50, "how many nodes per lap on the sphere");
    arg.param("laps", numLaps, 50, "how many times the robot travels around the sphere");
    arg.param("radius", radius, 100., "radius of the sphere");
    arg.param("noiseTranslation", noiseTranslation, std::vector<double>(), "set the noise level for the translation, separated by semicolons without spaces e.g: \"0.1;0.1;0.1\"");
    arg.param("noiseRotation", noiseRotation, std::vector<double>(), "set the noise level for the rotation, separated by semicolons without spaces e.g: \"0.001;0.001;0.001\"");
    arg.param("randomSeed", randomSeed, false, "use a randomized seed for generating the sphere");
    arg.parseArgs(argc, argv);

    if (noiseTranslation.size() == 0)
    {
        cerr << "using default noise for the translation" << endl;
        noiseTranslation.push_back(0.01);
        noiseTranslation.push_back(0.01);
        noiseTranslation.push_back(0.01);
    }
    cerr << "Noise for the translation:";
    for (size_t i = 0; i < noiseTranslation.size(); ++i)
        cerr << " " << noiseTranslation[i];
    cerr << endl;
    if (noiseRotation.size() == 0)
    {
        cerr << "using default noise for the rotation" << endl;
        noiseRotation.push_back(0.005);
        noiseRotation.push_back(0.005);
        noiseRotation.push_back(0.005);
    }
    cerr << "Noise for the rotation:";
    for (size_t i = 0; i < noiseRotation.size(); ++i)
        cerr << " " << noiseRotation[i];
    cerr << endl;

    Eigen::Matrix3d transNoise = Eigen::Matrix3d::Zero();
    /*
     0 0 0
     0 0 0
     0 0 0
     */

    for (int i = 0; i < 3; ++i)
    transNoise(i, i) = std::pow(noiseTranslation[i], 2);


    Eigen::Matrix3d rotNoise = Eigen::Matrix3d::Zero();
    for (int i = 0; i < 3; ++i)
        rotNoise(i, i) = std::pow(noiseRotation[i], 2);
    cout << "transNoise =" <<endl;
    cout << transNoise << endl;

    cout << "rotNoise =" <<endl;
    cout << rotNoise << endl;

    Eigen::Matrix<double, 6, 6> information = Eigen::Matrix<double, 6, 6>::Zero();
    information.block<3,3>(0,0) = transNoise.inverse();
    information.block<3,3>(3,3) = rotNoise.inverse();

    // information matrix represents how reliable this measurement is. Therefore, the more precisely the measurement is made or the more you trust in this measurement, the larger values in the information matrix you can set. (see http://fzheng.me/2016/03/15/g2o-demo/ )
    cout << "information =" <<endl;
    cout << information << endl;

    cout << "numLaps (how many times the robot travels around the sphere) = " << numLaps << endl;
    cout << "nodesPerLevel (how many nodes per lap on the sphere) = " << nodesPerLevel << endl;

    vector<VertexSE3*> vertices;
    vector<EdgeSE3*> odometryEdges;
    vector<EdgeSE3*> edges;
    
    // create the optimizer to load the data and carry out the optimization
    SparseOptimizer optimizer;
    
    int id = 0;
    FILE *fp = fopen("out_t.txt", "w+");
    for (int f = 0; f < numLaps; ++f)
    {
        for (int n = 0; n < nodesPerLevel; ++n)
        {
            VertexSE3* v = new VertexSE3;
            v->setId(id++);
            
            if(id==1)
            v->setFixed( true );

            Eigen::AngleAxisd rotz(-M_PI + 2*n*M_PI / nodesPerLevel, Eigen::Vector3d::UnitZ());
            Eigen::AngleAxisd roty(-0.5*M_PI + id*M_PI / (numLaps * nodesPerLevel), Eigen::Vector3d::UnitY());
            Eigen::Matrix3d rot = (rotz * roty).toRotationMatrix();

            Eigen::Isometry3d t;
            t = rot;
            t.translation() = t.linear() * Eigen::Vector3d(radius, 0, 0);
            //cout << t.translation().transpose() <<endl;;
            v->setEstimate(t);
            vertices.push_back(v);

            optimizer.addVertex(v);
            //row-wise
            fprintf(fp, "%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n",
                        t(0,0), t(0,1),t(0,2), t(0,3),
                        t(1,0), t(1,1),t(1,2), t(1,3),
                        t(2,0), t(2,1),t(2,2), t(2,3),
                        t(3,0), t(3,1),t(3,2), t(3,3) );
        }
    }
    fclose(fp);

    // generate odometry edges
    for (size_t i = 1; i < vertices.size(); ++i) {
        VertexSE3* prev = vertices[i-1];
        VertexSE3* cur  = vertices[i];
        Eigen::Isometry3d t = prev->estimate().inverse() * cur->estimate();
        EdgeSE3* e = new EdgeSE3;
        e->setVertex(0, prev);
        e->setVertex(1, cur);
        e->setMeasurement(t);
        e->setInformation(information);
        odometryEdges.push_back(e);
        edges.push_back(e);
        optimizer.addEdge(e);
    }

    // generate loop closure edges
    fp = fopen("out_loopclosure_from+to.txt", "w+");
    for (int f = 1; f < numLaps; ++f) {
        for (int nn = 0; nn < nodesPerLevel; ++nn) {
            VertexSE3* from = vertices[(f-1)*nodesPerLevel + nn];
            //row-wise
            Eigen::Isometry3d tf = from->estimate();

            for (int n = -1; n <= 1; ++n) // set three vertices
            {
                if (f == numLaps-1 && n == 1)
                    continue;
            //  VertexSE3* from = vertices[(f-1)*nodesPerLevel + nn];
                VertexSE3* to   = vertices[f*nodesPerLevel + nn + n]; // one-level위에서 3개의 vertices와 연결
                Eigen::Isometry3d t = from->estimate().inverse() * to->estimate();
                EdgeSE3* e = new EdgeSE3;
                e->setVertex(0, from);
                e->setVertex(1, to);
                e->setMeasurement(t);
                e->setInformation(information);
                edges.push_back(e);
                optimizer.addEdge(e); // what happens if commented out?
                
                Eigen::Isometry3d tt = to->estimate();
                fprintf(fp, "%f\t%f\t%f\t%f\t\t",   tf(0,3),tf(1,3),tf(2,3),tf(3,3) );
                fprintf(fp, "%f\t%f\t%f\t%f\n",     tt(0,3),tt(1,3),tt(2,3),tt(3,3) );
            }
            //fprintf(fp, "\n");
        }
    }
    fclose(fp);

    GaussianSampler<Eigen::Vector3d, Eigen::Matrix3d> transSampler;
    transSampler.setDistribution(transNoise);
    GaussianSampler<Eigen::Vector3d, Eigen::Matrix3d> rotSampler;
    rotSampler.setDistribution(rotNoise);

#if 0
    if (randomSeed)
    {
        std::random_device r;
        std::seed_seq seedSeq{r(), r(), r(), r(), r()};
        vector<int> seeds(2);
        seedSeq.generate(seeds.begin(), seeds.end());
        cerr << "using seeds:";
        for (size_t i = 0; i < seeds.size(); ++i)
            cerr << " " << seeds[i];
        cerr << endl;
        transSampler.seed(seeds[0]); // error ?
        rotSampler.seed(seeds[1]);
    }
#endif

    // noise for all the edges
    for (size_t i = 0; i < edges.size(); ++i)
    {
        EdgeSE3* e = edges[i];
        Eigen::Quaterniond gtQuat = (Eigen::Quaterniond)e->measurement().linear();
        Eigen::Vector3d gtTrans = e->measurement().translation();

        Eigen::Vector3d quatXYZ = rotSampler.generateSample();
        double qw = 1.0 - quatXYZ.norm();
        if (qw < 0)
        {
            qw = 0.;
            cerr << "x";
        }
        Eigen::Quaterniond rot(qw, quatXYZ.x(), quatXYZ.y(), quatXYZ.z());
        rot.normalize();
        Eigen::Vector3d trans = transSampler.generateSample();
        rot = gtQuat * rot;
        trans = gtTrans + trans;

        Eigen::Isometry3d noisyMeasurement = (Eigen::Isometry3d) rot;
        noisyMeasurement.translation() = trans;
        e->setMeasurement(noisyMeasurement);
    }


    // concatenate all the odometry constraints to compute the initial state
    // An hyper graph is a graph where an edge can connect one or more nodes.
    for (size_t i =0; i < odometryEdges.size(); ++i)
    {
        EdgeSE3* e = edges[i];
        VertexSE3* from = static_cast<VertexSE3*>(e->vertex(0));
        VertexSE3* to = static_cast<VertexSE3*>(e->vertex(1));
        HyperGraph::VertexSet aux;
        aux.insert(from);
        e->initialEstimate(aux, to);
    }

    // write output
    ofstream fileOutputStream;
    if (outFilename != "-")
    {
        //cerr << "Writing into " << outFilename << endl;
        //fileOutputStream.open(outFilename.c_str());
    }
    else
    {
        //cerr << "writing to stdout" << endl;
        outFilename = "out_vertex+edge.g2o";

    }
    cerr << "Writing into " << outFilename << endl;
    fileOutputStream.open(outFilename.c_str());

    string vertexTag = Factory::instance()->tag(vertices[0]);
    string edgeTag = Factory::instance()->tag(edges[0]);
    cout << "vertexTag = "<< vertexTag << endl;
    cout << "edgeTag = "<< edgeTag << endl;
    
    ostream& fout = outFilename != "-" ? fileOutputStream : cout;
    for (size_t i = 0; i < vertices.size(); ++i)
    {
        VertexSE3* v = vertices[i];
        fout << vertexTag << " " << v->id() << " ";
        v->write(fout);
        fout << endl;
    }


    for (size_t i = 0; i < edges.size(); ++i)
    {
        EdgeSE3* e = edges[i];
        VertexSE3* from = static_cast<VertexSE3*>(e->vertex(0));
        VertexSE3* to = static_cast<VertexSE3*>(e->vertex(1));
        fout << edgeTag << " " << from->id() << " " << to->id() << " ";
        e->write(fout);
        fout << endl;
    }

    // write output
    fp = fopen("out_vertices_before.txt", "w");
    for(int i=0; i<vertices.size(); i++)
    {
     
        Eigen::Isometry3d t = vertices[i]->estimate();
        //cout<<"vertex pose(before)="<<endl<<t.matrix()<<endl;
        
        fprintf(fp, "%f\t%f\t%f\t%f\n",   t(0,3),t(1,3),t(2,3),t(3,3) );
        
    }
    fclose(fp);
    
    
    // create the linear solver
    BlockSolverX::LinearSolverType * linearSolver = new LinearSolverCSparse<BlockSolverX::PoseMatrixType>();
    
    // create the block solver on top of the linear solver
    BlockSolverX* blockSolver = new BlockSolverX(linearSolver);

    
    // create the algorithm to carry out the optimization
    //OptimizationAlgorithmGaussNewton* optimizationAlgorithm = new OptimizationAlgorithmGaussNewton(blockSolver);
    OptimizationAlgorithmLevenberg* optimizationAlgorithm = new OptimizationAlgorithmLevenberg(blockSolver);

    
    optimizer.setVerbose(true);
    optimizer.setAlgorithm(optimizationAlgorithm);
    
    int maxIterations = 10;
    
    
    optimizer.initializeOptimization();
    optimizer.optimize(maxIterations);

    // Visulizing only points (w/o pose)
    fp = fopen("out_vertices_after.txt", "w");
    for(size_t i=0; i<vertices.size(); i++)
    //for(int i=0; i<2; i++)
    {
        g2o::VertexSE3* v = dynamic_cast<g2o::VertexSE3*>( optimizer.vertex(i) );
        Eigen::Isometry3d t = v->estimate();
        //cout<<"vertex pose(after)="<<endl<<t.matrix()<<endl;
        
        fprintf(fp, "%f\t%f\t%f\t%f\n",   t(0,3),t(1,3),t(2,3),t(3,3) );
        
    }
    fclose(fp);
    
    cout << "Done!!! " << endl;
    return 0;
}
