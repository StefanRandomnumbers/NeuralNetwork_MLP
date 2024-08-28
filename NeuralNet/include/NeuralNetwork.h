#pragma once
#include <stdio.h>
#include <vector>
#include <qlist.h>
#include <qpair.h>
#include "Layer.h"
#include "Weight.h"

using namespace std;

class NeuralNetwork
{
public:
    NeuralNetwork(vector<int> layerInfo, double learnFactor);
    ~NeuralNetwork();

    Layer feedforward(Layer input);
    double cost();
    double train(QPair<QList<Layer>, QList<Layer>> trainData, QPair<QList<Layer>, QList<Layer>> testData);
    double train(QPair<Layer, Layer> trainData, QPair<Layer, Layer> testData);
    void backpropagation(Layer costDeriv);

//private:
    vector<int> m_layerInfo;
    int m_nHiddenLayers;
    double m_learnFactor;

    //QList<Layer> m_z;    // the layers activation befor the activation function (sigmoid)
    QList<Layer> m_layers;   // the layers activation after the activation function (sigmoid)
    QList<Weight> m_weights; // all the weights 
    QList<Layer> m_bias;    // all the bias weights

    QList<Weight> m_weightsDerivVelocity;   // the velocity of the weight deriv that will determine how the weights will be adjusted
    QList<Layer> m_biasDerivVelocity;    // the velocity of the bias deriv that will determine how the weights will be adjusted
};