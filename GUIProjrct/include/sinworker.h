#ifndef SINWORKER_H
#define SINWORKER_H

#include <QtCore>
#include "NeuralNetwork.h"
#include "Weight.h"

class SinWorker :
    public QObject
{
    Q_OBJECT

public:
    SinWorker(QVector<int> layerInfo, double learnFactor);
    virtual ~SinWorker();

    Q_INVOKABLE void runTraining();
    QPair<QVector<double>, QVector<double>> calculateResult();

    void start();
    void stop();

    void newNN(QVector<int> layerInfo, double learnFactor);

    QPair< QList<Layer>, QList<Layer> > trainData() { return m_trainData; }
    QPair< QList<Layer>, QList<Layer> > testData() { return m_testData; }

signals:
    void epochFinished(double trainCost, double testCost);
    void sinResults(QPair<QVector<double>, QVector<double>> result);

private:
    NeuralNetwork *mp_nn;

    QPair< QList<Layer>, QList<Layer> > m_trainData;
    QPair< QList<Layer>, QList<Layer> > m_testData;

    bool m_runing = false;
};

#endif // SINWORKER_H
