#include "Weight.h"
#include "Layer.h"
#include "NeuralNetwork.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <qpair.h>
#include <cstdlib>
#include <ctime>
#include <cmath>


int main(int argc, char *argv[])
{
    srand(time(0));

    int nnInfo[] = {2, 2, 1};
    std::vector<int> layerStructure(nnInfo, nnInfo + sizeof(nnInfo) / sizeof(int));

    NeuralNetwork nn(layerStructure, 0.1);


    std::cout << "feedforward test: \n\n";

    std::cout << "input: ";
    QList<Layer> trainIn;
    QList<Layer> trainOut;

    Layer input(2);
    Layer label(1);

    input.at(0) = 0;
    input.at(1) = 0;
    label.at(0) = 0;
    trainIn.push_back(input);
    trainOut.push_back(label);

    input.at(0) = 0;
    input.at(1) = 1;
    label.at(0) = 1;
    trainIn.push_back(input);
    trainOut.push_back(label);

    input.at(0) = 1;
    input.at(1) = 0;
    label.at(0) = 1;
    trainIn.push_back(input);
    trainOut.push_back(label);

    input.at(0) = 1;
    input.at(1) = 1;
    label.at(0) = 0;
    trainIn.push_back(input);
    trainOut.push_back(label);

    QPair< QList<Layer>, QList<Layer> > trainData(trainIn, trainOut);

    double cost = 10000;
    while (cost > 0.1)
    {
        cost = nn.train(trainData, trainData);
        std::cout << "\n cost: " << cost;

        int rightClassif = 0;
        for (int i = 0; i < trainIn.size(); i++)
        {
            int res;
            if (nn.feedforward(trainIn[i]).at(0) >= 0.5)
            {
                res = 1;
            }
            else
            {
                res = 0;
            }
            if (res == trainOut[i].at(0))
            {
                rightClassif++;
            }
        }
        std::cout << "\n right: " << rightClassif;
    }


    /*std::cout << "\nbias: ";
    nn.m_bias[0].at(0) = 1;
    nn.m_bias[0].at(1) = -2;
    nn.m_bias[0].print();

    nn.m_bias[1].at(0) = 0.5;
    nn.m_bias[1].print();

    std::cout << "\nweihts: ";
    nn.m_weights[0].at(0, 0) = 0.5;
    nn.m_weights[0].at(1, 0) = 0.1;
    nn.m_weights[0].at(0, 1) = -0.3;
    nn.m_weights[0].at(1, 1) = 0.6;
    nn.m_weights[0].print();

    nn.m_weights[1].at(0, 0) = -0.5;
    nn.m_weights[1].at(0, 1) = 0.2;
    nn.m_weights[1].print();

    nn.feedforward(input).print();


    Layer testIn(2);
    testIn.at(0) = 1;
    testIn.at(1) = 0;
    Layer testLab(1);
    testLab.at(0) = 1;

    nn.train(QPair<Layer, Layer>(input, label), QPair<Layer, Layer>(testIn, testLab));
    */
    return 0;
}