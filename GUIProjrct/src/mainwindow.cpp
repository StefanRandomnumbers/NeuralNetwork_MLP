#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Weight.h"
#include <QtCore/QDebug>
#include "NNSettingsDialog.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mp_ui(new Ui::MainWindow),
    mp_errorChart(new ErrorChart(100)),
    mp_resultChart(new QChart()),
    mp_resultSeries(new QScatterSeries()),
    mp_resultSeriesTrainData(new QScatterSeries()),
    mp_resultSeriesTestData(new QScatterSeries()),
    mp_workerThread(new QThread()),
    m_learnFactor(0.04)

{
    srand(time(0));

    mp_ui->setupUi(this);
    

    qRegisterMetaType<Weight>("Weight");
    qRegisterMetaType<QPair<QVector<double>, QVector<double>>>("QPair<QVector<double>, QVector<double>>");


    mp_resultChart->addSeries(mp_resultSeries);
    mp_resultChart->addSeries(mp_resultSeriesTrainData);
    mp_resultChart->addSeries(mp_resultSeriesTestData);
    mp_axisX = new QValueAxis();
    mp_axisX->setRange(0, 1);
    mp_axisX->setTickCount(2);
    mp_axisY = new QValueAxis();
    mp_axisY->setRange(0, 1);
    mp_axisY->setTickCount(2);
    mp_resultChart->addAxis(mp_axisX, Qt::AlignBottom);
    mp_resultChart->addAxis(mp_axisY, Qt::AlignLeft);
    mp_resultSeries->attachAxis(mp_axisX);
    mp_resultSeries->attachAxis(mp_axisY);
    mp_resultSeriesTrainData->attachAxis(mp_axisX);
    mp_resultSeriesTrainData->attachAxis(mp_axisY);

    mp_resultSeriesTrainData->setBrush(QColor(255, 0, 0));
    mp_resultSeriesTrainData->setMarkerSize(10);
    mp_resultSeriesTrainData->setName("Train Data(noisy Sinus)");


    mp_resultSeriesTestData->attachAxis(mp_axisX);
    mp_resultSeriesTestData->attachAxis(mp_axisY);

    mp_resultSeriesTestData->setBrush(QColor(0, 255, 0));
    mp_resultSeriesTestData->setMarkerSize(10);
    mp_resultSeriesTestData->setName("Test Data");


    mp_resultSeries->setMarkerSize(12);
    mp_resultSeries->setName("Result of NN");

    mp_ui->chartView_result->setChart(mp_resultChart);
    mp_ui->chartView_error->setChart(mp_errorChart);



    m_layerInfo = {2, 2, 1};
    mp_xorworker = new XORWorker(m_layerInfo, m_learnFactor);
    mp_sinworker = new SinWorker(m_layerInfo, m_learnFactor);
    QObject::connect(mp_xorworker, SIGNAL(epochFinished(double, double)), this, SLOT(updateErrorChart(double, double)));
    QObject::connect(mp_sinworker, SIGNAL(epochFinished(double, double)), this, SLOT(updateErrorChart(double, double)));
    QObject::connect(mp_xorworker, SIGNAL(xorResults(Weight)), this, SLOT(updateResultChart(Weight)));
    QObject::connect(mp_sinworker, SIGNAL(sinResults(QPair<QVector<double>, QVector<double>>)), this, SLOT(updateResultChart(QPair<QVector<double>, QVector<double>>)));

    QObject::connect(mp_ui->pushButton_start, SIGNAL(toggled(bool)), this, SLOT(on_pushButton_start_toggled(bool)));
    QObject::connect(mp_ui->pushButton_reset, SIGNAL(clicked()), this, SLOT(resetNN()));

    QObject::connect(mp_ui->actionXOR, SIGNAL(triggered(bool)), this, SLOT(activateXORWorker(bool)));
    QObject::connect(mp_ui->actionSinus, SIGNAL(triggered(bool)), this, SLOT(activateSinWorker(bool)));
    QObject::connect(mp_ui->actionNetwork_Settings, SIGNAL(triggered()), this, SLOT(nnSettingsActionTriggered()));


    // move the worker to a differnet thread
    mp_xorworker->moveToThread(mp_workerThread);
    mp_sinworker->moveToThread(mp_workerThread);
    mp_workerThread->start();
}

MainWindow::~MainWindow()
{
    delete mp_errorChart;
    delete mp_resultChart;
    delete mp_resultSeries;
    delete mp_workerThread;
    delete mp_xorworker;
    delete mp_axisX;
    delete mp_axisY;

    delete mp_ui;
}


void MainWindow::updateErrorChart(double trainCost, double testCost)
{
    mp_errorChart->addNewPoint(trainCost, testCost);
}

void MainWindow::updateResultChart(Weight result)
{
    mp_resultSeries->clear();

    for(int i = 0; i < result.rows(); i++)
    {
        for(int j = 0; j < result.cols(); j++)
        {
            if(result.at(i, j) >= 0.9)
            {
                // draw a dot on the chart
                mp_resultSeries->append(static_cast<qreal>(i)/10, static_cast<qreal>(j)/10);
            }
        }
    }
}
// result: first = testIn; second = feedforward(testIn)
void MainWindow::updateResultChart(QPair<QVector<double>, QVector<double>> result)
{
    mp_resultSeries->clear();

    for(int i = 0; i < result.first.size(); i++)
    {
        mp_resultSeries->append(result.first.at(i) * 2 * M_PI, result.second.at(i));
    }
}

void MainWindow::on_pushButton_start_toggled(bool checked)
{
    if(checked)
    {
        // start the worker
        if(m_runXor && !m_runSin)
        {
            mp_xorworker->start();
        }
        else
        {
            mp_sinworker->start();
        }
        mp_ui->pushButton_start->setText("Stop");
        mp_ui->pushButton_reset->setEnabled(false);
        mp_ui->actionNetwork_Settings->setEnabled(false);
        mp_ui->actionSinus->setEnabled(false);
        mp_ui->actionXOR->setEnabled(false);
    }
    else
    {
        // stop the worker
        if(m_runXor && !m_runSin)
        {
            mp_xorworker->stop();
        }
        else
        {
            mp_sinworker->stop();
        }
        mp_ui->pushButton_start->setText("Start");
        mp_ui->pushButton_reset->setEnabled(true);
        mp_ui->actionNetwork_Settings->setEnabled(true);
        mp_ui->actionSinus->setEnabled(true);
        mp_ui->actionXOR->setEnabled(true);
    }
}

void MainWindow::resetNN()
{
    mp_errorChart->resetSeries();
    mp_sinworker->newNN(m_layerInfo, m_learnFactor);
    mp_xorworker->newNN(m_layerInfo, m_learnFactor);
}

void MainWindow::activateSinWorker(bool b)
{
    if (b)
    {
        m_runXor = false;
        m_runSin = true;
        mp_ui->actionSinus->setChecked(true);
        mp_ui->actionXOR->setChecked(false);

        resetNN();

        mp_axisX->setRange(0, 7);
        mp_axisX->setTickCount(8);
        mp_axisY->setRange(-1, 1);
        mp_axisY->setTickCount(3);

        // handle the result chart
        mp_resultSeries->clear();
        displaySinusData();
    }
}

void MainWindow::activateXORWorker(bool b)
{
    if (b)
    {
        m_runXor = true;
        m_runSin = false;
        mp_ui->actionSinus->setChecked(false);
        mp_ui->actionXOR->setChecked(true);

        resetNN();

        mp_axisX->setRange(0, 1);
        mp_axisX->setTickCount(2);
        mp_axisY->setRange(0, 1);
        mp_axisY->setTickCount(2);

        // handle the result chart
        mp_resultSeries->clear();
        mp_resultSeriesTrainData->clear();
    }
}
void MainWindow::displaySinusData()
{
    QPair< QList<Layer>, QList<Layer> > trainData = mp_sinworker->trainData();
    QPair< QList<Layer>, QList<Layer> > testData = mp_sinworker->testData();
    
    // add the data to the resultseriestrain/test
    for (int i = 0; i < trainData.first.size(); i++)
    {
        mp_resultSeriesTrainData->append(trainData.first[i].at(0) * 2 * M_PI, trainData.second[i].at(0));
        mp_resultSeriesTestData->append(testData.first[i].at(0) * 2 * M_PI, testData.second[i].at(0));
    }
}

void MainWindow::nnSettingsActionTriggered()
{
    NNSettingsDialog nnSettingsDialog(m_layerInfo, m_learnFactor, this);
    const int retDialog = nnSettingsDialog.exec();
    if (QDialog::Accepted == retDialog)
    {
        m_layerInfo = nnSettingsDialog.getLayerInfo();
        m_learnFactor = nnSettingsDialog.getLearnFactor();

        resetNN();
    }
}