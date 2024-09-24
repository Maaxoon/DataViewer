#include "data.h"


std::istream& operator>>(std::istream& is, DataRow& row)
{
    return is >> row.freq >> row.real >> row.imag;
}
