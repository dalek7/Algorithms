
// based on https://github.com/RainerKuemmerle/g2o/blob/master/g2o/examples/sphere/create_sphere.cpp
// written by Seung-Chan Kim


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

    cout << "Hello world!" << endl;
    return 0;
}
