#include "sinworker.h"
#include <math.h>
#include <random>

SinWorker::SinWorker(QVector<int> layerInfo, double learnFactor) :
    mp_nn(new NeuralNetwork(layerInfo, learnFactor))
{
    srand(time(0));
    // create the train and test data for the Sinus training

    // test data
    int numberOfData = 20;
    QList<Layer> trainIn;
    QList<Layer> trainOut;
    QList<Layer> testIn;
    QList<Layer> testOut;
    for(int i = 0; i < numberOfData; i++)
    {
        Layer in(1, 0);
        in.at(0) = static_cast<double>(i) / (numberOfData-1);

        Layer out(1, 0);
        double noiseAmp = 0.3;
        out.at(0) = (sin(in.at(0) * 2 * M_PI)) + ((static_cast<double>(rand()) / (RAND_MAX)) * noiseAmp - noiseAmp / 2);   // sin(x) + noise
        trainIn.push_back(in);
        trainOut.push_back(out);


        out.at(0) = (sin(in.at(0) * 2 * M_PI));
        testIn.push_back(in);
        testOut.push_back(out);
    }
    m_trainData = QPair< QList<Layer>, QList<Layer> >(trainIn, trainOut);
    m_testData = QPair< QList<Layer>, QList<Layer> >(testIn, testOut);
}




SinWorker::~SinWorker()
{
    delete mp_nn;
}


// is the main function of the worker
void SinWorker::runTraining()
{
    int count = 0;
    while(m_runing)
    {
        QPair<double, double> cost = mp_nn->train(m_trainData, m_testData);
        // emit a signal to the gui to display the cost in the error chart
        if (count % 500 == 0)
        {
            emit epochFinished(cost.first, cost.second);
            // calculate the results
            emit sinResults(calculateResult());

            QThread::msleep(50);
        }
        count++;
    }
}

QPair<QVector<double>, QVector<double>> SinWorker::calculateResult()
{
    QVector<double> resultY;
    QVector<double> resultX;
    for(int i = 0; i < m_trainData.first.size(); i++)
    {
        double res = mp_nn->feedforward(m_trainData.first.at(i)).at(0);
        resultY.push_back(res);
        resultX.push_back(m_trainData.first.at(i).at(0));
    }
    return QPair<QVector<double>, QVector<double>>(resultX, resultY);
}



void SinWorker::start()
{
    m_runing = true;
    QMetaObject::invokeMethod(this, "runTraining");
}
void SinWorker::stop()
{
    m_runing = false;
}

void SinWorker::newNN(QVector<int> layerInfo, double learnFactor)
{
    delete mp_nn;
    mp_nn = new NeuralNetwork(layerInfo, learnFactor);
}
