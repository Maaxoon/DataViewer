#ifndef DATAPARSER_H
#define DATAPARSER_H

#include "data.h"

class DataParser
{
public:
    DataParser();
    DataValues Parse(std::istream& in);
private:
    bool CheckHeader(std::istream& in);
};

#endif // DATAPARSER_H
