#ifndef XORWORKER_H
#define XORWORKER_H

#include <QtCore>
#include "NeuralNetwork.h"
#include "Weight.h"

class XORWorker :
    public QObject
{
    Q_OBJECT

public:
    XORWorker(QVector<int> layerInfo, double learnFactor);
    virtual ~XORWorker();

    Q_INVOKABLE void runTraining();
    Weight calculateResult();

    void start();
    void stop();
    void newNN(QVector<int> layerInfo, double learnFactor);

signals:
    void epochFinished(double trainCost, double testCost);
    void xorResults(Weight result);

private:
    NeuralNetwork *mp_nn;

    QPair< QList<Layer>, QList<Layer> > m_trainData;

    bool m_runing = false;
};

#endif // XORWORKER_H
