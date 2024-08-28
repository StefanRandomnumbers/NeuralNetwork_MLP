#include "xorworker.h"
#include "Weight.h"
#include "Layer.h"
#include <qdebug.h>
#include <qthread.h>

XORWorker::XORWorker(QVector<int> layerInfo, double learnFactor) :
    mp_nn(new NeuralNetwork(layerInfo, learnFactor))
{
    // create the train and test data for the XOR training
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

    m_trainData = QPair< QList<Layer>, QList<Layer> >(trainIn, trainOut);

}

XORWorker::~XORWorker()
{
    delete mp_nn;
}


// is the main function of the worker
void XORWorker::runTraining()
{
    int count = 0;
    while(m_runing)
    {
        QPair<double, double> cost = mp_nn->train(m_trainData, m_trainData);

        if (count % 900 == 0)
        {
            // emit a signal to the gui to display the cost in the error chart
            emit epochFinished(cost.first, cost.second);
            // calculate the results
            emit xorResults(calculateResult());

            QThread::msleep(90);
        }
    }
}

Weight XORWorker::calculateResult()
{
    Weight mat(11, 11, 0);
    for(int i = 0; i <= 10; i++)
    {
        Layer input(2, 0);
        input.at(0) = static_cast<double>(i)/10;
        for(int j = 0; j <= 10; j++)
        {
            input.at(1) = static_cast<double>(j)/10;
            if(mp_nn->feedforward(input).at(0) >= 0.5)
            {
                mat.at(i, j) = 1;
            }
            else
            {
                mat.at(i, j) = 0;
            }

        }
    }
    return  mat;
}



void XORWorker::start()
{
    m_runing = true;
    QMetaObject::invokeMethod(this, "runTraining");
}
void XORWorker::stop()
{
    m_runing = false;
}

void XORWorker::newNN(QVector<int> layerInfo, double learnFactor)
{
    delete mp_nn;
    mp_nn = new NeuralNetwork(layerInfo, learnFactor);
}