
// based on https://github.com/RainerKuemmerle/g2o/blob/master/g2o/examples/sphere/create_sphere.cpp
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

using namespace std;
using namespace g2o;


using namespace std;

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

    cout << "information =" <<endl;
    cout << information << endl;


    cout << "numLaps (how many times the robot travels around the sphere) = " << numLaps << endl;
    cout << "nodesPerLevel (how many nodes per lap on the sphere) = " << nodesPerLevel << endl;
    vector<VertexSE3*> vertices;
    vector<EdgeSE3*> odometryEdges;
    vector<EdgeSE3*> edges;
    int id = 0;
    FILE *fp = fopen("out_t.txt", "w+");
    for (int f = 0; f < numLaps; ++f)
    {
        for (int n = 0; n < nodesPerLevel; ++n)
        {
            VertexSE3* v = new VertexSE3;
            v->setId(id++);

            Eigen::AngleAxisd rotz(-M_PI + 2*n*M_PI / nodesPerLevel, Eigen::Vector3d::UnitZ());
            Eigen::AngleAxisd roty(-0.5*M_PI + id*M_PI / (numLaps * nodesPerLevel), Eigen::Vector3d::UnitY());
            Eigen::Matrix3d rot = (rotz * roty).toRotationMatrix();

            Eigen::Isometry3d t;
            t = rot;
            t.translation() = t.linear() * Eigen::Vector3d(radius, 0, 0);
            //cout << t.translation().transpose() <<endl;;
            v->setEstimate(t);
            vertices.push_back(v);

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
    }

    // generate loop closure edges
    fp = fopen("out_loopclosure_from+to.txt", "w+");
    for (int f = 1; f < numLaps; ++f) {
        for (int nn = 0; nn < nodesPerLevel; ++nn) {
            VertexSE3* from = vertices[(f-1)*nodesPerLevel + nn];
            //row-wise
            Eigen::Isometry3d tf = from->estimate();
            //fprintf(fp, "%f\t%f\t%f\t%f\t\t", tf(0,3),tf(1,3),tf(2,3),tf(3,3) );

            
            for (int n = -1; n <= 1; ++n)
            {
                if (f == numLaps-1 && n == 1)
                    continue;
                VertexSE3* to   = vertices[f*nodesPerLevel + nn + n];
                Eigen::Isometry3d t = from->estimate().inverse() * to->estimate();
                EdgeSE3* e = new EdgeSE3;
                e->setVertex(0, from);
                e->setVertex(1, to);
                e->setMeasurement(t);
                e->setInformation(information);
                edges.push_back(e);
                Eigen::Isometry3d tt = to->estimate();
                fprintf(fp, "%f\t%f\t%f\t%f\t\t",   tf(0,3),tf(1,3),tf(2,3),tf(3,3) );
                fprintf(fp, "%f\t%f\t%f\t%f\n",     tt(0,3),tt(1,3),tt(2,3),tt(3,3) );
            }
            //fprintf(fp, "\n");
        }
    }
    fclose(fp);

    cout << "Hello world!!! " << endl;
    return 0;
}
