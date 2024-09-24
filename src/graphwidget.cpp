#include "graphwidget.h"
#include <QPainter>
#include <cmath>

GraphWidget::GraphWidget(QWidget *parent)
    : QFrame(parent)
{
    setFrameShape(QFrame::Box);
}

void GraphWidget::setData(const DataValues& newData)
{
    // Задаем новые данные и запускаем перерисовку
    data = newData;
    update();
}

void GraphWidget::paintEvent(QPaintEvent*)
{
    if (data.empty()) {
        return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::red, 2));

    double minX = data[0].freq;
    double maxX = minX;
    double minY = getLogMag(data[0]);
    double maxY = minY;

    // Поиск граничных значений координат
    for (const auto& row : data) {
        double logMag = getLogMag(row);
        if (row.freq < minX) minX = row.freq;
        if (row.freq > maxX) maxX = row.freq;
        if (logMag < minY) minY = logMag;
        if (logMag > maxY) maxY = logMag;
    }

    int width = this->width();
    int height = this->height();

    // Линейные преобразования координат графиков
    auto getRealX = [&](double x) {
        return (x - minX) / (maxX - minX) * (width - 50) + 35;
    };

    auto getRealY = [&](double y) {
        return height - (y - minY) / (maxY - minY) * (height - 50) - 30;
    };

    painter.setPen(QPen(Qt::black, 2));

    // Отображение оси X
    painter.drawLine(35, height - 30, width, height - 30);
    painter.drawText(width - 50, height - 5, "Частота");

    // Отображение оси Y
    painter.drawLine(35, 0, 35, height - 30);
    painter.drawText(0, 10, "S11");

    // Засечки и значения для оси Х
    const int numXTicks = std::log2(data.size());
    for (int i = 0; i <= numXTicks; ++i) {
        double xValue = minX + i * (maxX - minX) / numXTicks;
        int xScreen = getRealX(xValue);
        painter.drawLine(xScreen, height - 30, xScreen, height - 26);
        painter.drawText(xScreen - 30, height - 15, QString::number(xValue, 'E', 2));
    }

    // Засечки и значения для оси Y
    const int numYTicks = std::log2(data.size());
    for (int i = 0; i <= numYTicks; ++i) {
        double yValue = minY + i * (maxY - minY) / numYTicks;
        int yScreen = getRealY(yValue);
        painter.drawLine(30, yScreen, 35, yScreen);
        painter.drawText(0, yScreen + 5, QString::number(yValue, 'f', 2));
    }

    // Рисуем график "точки, соединенные линиями"
    painter.setPen(QPen(Qt::red, 1));
    for (int i = 1; i < data.size(); ++i) {
        double y1 = getLogMag(data[i-1]);
        double y2 = getLogMag(data[i]);

        painter.drawLine(getRealX(data[i-1].freq), getRealY(y1),
                getRealX(data[i].freq), getRealY(y2));
    }
}

double GraphWidget::getLogMag(const DataRow & data)
{
    return 20 * std::log10(std::sqrt(data.real * data.real + data.imag * data.imag));
}
