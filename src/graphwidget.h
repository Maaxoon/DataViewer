#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include "data.h"
#include <QFrame>

class GraphWidget : public QFrame
{
    Q_OBJECT

public:
    explicit GraphWidget(QWidget *parent = nullptr);
    void setData(const DataValues& newData);
protected:
    void paintEvent(QPaintEvent*) override;
private:
    double getLogMag(const DataRow & data);
    DataValues data;
};


#endif // GRAPHWIDGET_H
