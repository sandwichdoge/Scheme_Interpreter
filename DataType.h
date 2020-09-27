#ifndef INCLUDE_DATATYPE_H
#define INCLUDE_DATATYPE_H
#include <string>
#include <iostream>

class DataType {
public:
    enum DATA_TYPE {DATA_TYPE_UNDEFINED, DATA_TYPE_DOUBLE, DATA_TYPE_STRING};
    DataType operator+(const DataType& data);
    DataType operator-(const DataType& data);
    DataType operator*(const DataType& data);
    DataType operator/(const DataType& data);

    DataType operator<(const DataType& data);
    DataType operator<=(const DataType& data);
    DataType operator>(const DataType& data);
    DataType operator>=(const DataType& data);
    DataType operator==(const DataType& data);
    bool operator==(const double data);  // Internal use.
    DataType operator!=(const DataType& data);

    DataType operator&&(const DataType& data);
    DataType operator||(const DataType& data);

    void operator=(const DataType& data);
    void operator=(const int target);
    void operator=(const double data);
    void operator=(const std::string& data);

    friend std::ostream& operator<<(std::ostream& os, const DataType& data);

    enum DATA_TYPE dataType = DATA_TYPE_UNDEFINED;
    std::string _stringData;
    double _doubledata;
};

#endif
