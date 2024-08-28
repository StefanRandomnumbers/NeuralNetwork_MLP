#ifndef CHART_H
#define CHART_H

#include <QtCharts/QChart>
#include <qxyseries.h>
#include <qlineseries.h>
#include <qlist.h>
#include <QValueAxis>

QT_CHARTS_USE_NAMESPACE

class ErrorChart : public QChart
{
public:
    ErrorChart(int xMax, QGraphicsItem *parent = nullptr);
    ~ErrorChart();
    void addNewPoint(qreal trainError, qreal testError);

    QValueAxis* axisX() { return mp_axisX;}
    QValueAxis* axisY() { return mp_axisY;}

    void resetSeries();

private:
    QLineSeries *mp_testSeries;
    QLineSeries *mp_trainSeries;
    QValueAxis *mp_axisX;
    QValueAxis *mp_axisY;
    qreal m_x;
};

#endif // CHART_H
