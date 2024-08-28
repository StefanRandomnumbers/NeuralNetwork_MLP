#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <qscatterseries.h>
#include <qthread.h>
#include "errorchart.h"
#include "xorworker.h"
#include "sinworker.h"

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow :
    public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void displaySinusData();
public slots:
    void updateErrorChart(double trainCost, double testCost);
    void updateResultChart(Weight result);
    void updateResultChart(QPair<QVector<double>, QVector<double>> result);

    void on_pushButton_start_toggled(bool checked);
    void resetNN();
    void activateSinWorker(bool b);
    void activateXORWorker(bool b);
    void nnSettingsActionTriggered();

private:
    Ui::MainWindow *mp_ui;

    ErrorChart* mp_errorChart;
    QChart* mp_resultChart;
    QScatterSeries* mp_resultSeries;
    QScatterSeries* mp_resultSeriesTrainData;
    QScatterSeries* mp_resultSeriesTestData;
    QValueAxis *mp_axisX;
    QValueAxis *mp_axisY;

    QThread *mp_workerThread;
    XORWorker *mp_xorworker;
    SinWorker *mp_sinworker;
    QVector<int> m_layerInfo;
    double m_learnFactor;

    bool m_runXor = true;
    bool m_runSin = false;

    int m_epochCount = 0;
};

#endif // MAINWINDOW_H
