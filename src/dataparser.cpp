#include "dataparser.h"
#include "data.h"

DataParser::DataParser()
{

}

DataValues DataParser::Parse(std::istream &in)
{
    DataValues data;
    DataRow row;

    if (!CheckHeader(in)){
        throw std::runtime_error("ошибка считывания заголовка данных");
    }

    while (in >> row)
    {
        data.push_back(row);

        if (in.fail() && !in.eof())
        {
            throw std::runtime_error("ошибка считывания данных");
        }
    }

    return data;
}

bool DataParser::CheckHeader(std::istream &in)
{
    std::string header;

    std::getline(in, header);
    if (header[0] != '#')
    {
        return false;
    }
    std::getline(in, header);
    if (header[0] != '!')
    {
        return false;
    }
    std::getline(in, header);
    if (header[0] != '!')
    {
        return false;
    }

    return true;
}

