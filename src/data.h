#ifndef DATA_H
#define DATA_H

#include <QVector>
#include <istream>

struct DataRow
{
    explicit DataRow() : freq(0), real(0), imag(0){};
    double freq;
    double real;
    double imag;
};

std::istream& operator>>(std::istream& is, DataRow& row);

using DataValues = QVector<DataRow>;

#endif // DATA_H
