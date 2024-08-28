#include "errorchart.h"
#include "qdebug.h"

ErrorChart::ErrorChart(int xMax, QGraphicsItem *parent) :
    QChart(parent),
    mp_testSeries(new QLineSeries()),
    mp_trainSeries(new QLineSeries()),
    mp_axisX(new QValueAxis()),
    mp_axisY(new QValueAxis()),
    m_x(xMax)
{
    addSeries(mp_testSeries);
    addSeries(mp_trainSeries);

    addAxis(mp_axisX,Qt::AlignBottom);
    addAxis(mp_axisY,Qt::AlignLeft);

    mp_testSeries->setPen(QPen(QColor(0, 0, 255)));
    mp_trainSeries->setPen(QPen(QColor(255, 0, 0)));


    mp_testSeries->attachAxis(mp_axisX);
    mp_testSeries->attachAxis(mp_axisY);
    mp_trainSeries->attachAxis(mp_axisX);
    mp_trainSeries->attachAxis(mp_axisY);

    mp_axisX->setRange(0, xMax);
    mp_axisY->setRange(0, 1.2);
    mp_axisY->setTickCount(4 + 1);
    mp_axisX->setTickCount(xMax + 1);

    mp_trainSeries->setName("train cost");
    mp_testSeries->setName("test cost");
}

ErrorChart::~ErrorChart()
{
    delete mp_testSeries;
    delete mp_trainSeries;
    delete mp_axisX;
    delete mp_axisY;
}


void ErrorChart::addNewPoint(qreal trainError, qreal testError)
{
    qDebug() << "train: " << trainError << " test: " << testError;
    qreal x = plotArea().width() / mp_axisX->tickCount();
    m_x += (mp_axisX->max() - mp_axisX->min()) / mp_axisX->tickCount();

    // append the new points
    mp_trainSeries->append(m_x, trainError);
    mp_testSeries->append(m_x, testError);


    scroll(x, 0);
}

void ErrorChart::resetSeries()
{
    mp_testSeries->clear();
    mp_trainSeries->clear();
}
