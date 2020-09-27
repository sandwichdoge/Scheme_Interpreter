#include "DataType.h"
#include "Utils/Debug.h"
#include "Utils/FloatUtils.h"

/* 4 cases:
 - self: double, target: double
 - self: double, target: string
 - self: string, target: double
 - self: string, target: string
*/
DataType DataType::operator+(const DataType& target) {
    DataType ret;
    //db("Self's type:" << this->dataType);
    //db("Target's type:" << target.dataType);
    switch (this->dataType) {
        case DATA_TYPE_DOUBLE: {
            switch (target.dataType) {
                case DATA_TYPE_DOUBLE: {
                    ret.dataType = DATA_TYPE_DOUBLE;
                    ret._doubledata = target._doubledata + this->_doubledata;
                    break;
                }
                case DATA_TYPE_STRING: {
                    db("Error. Cannot add number to string.");
                    exit(-1);
                    break;
                }
            }
            break;
        }
        case DATA_TYPE_STRING: {
            switch (target.dataType) {
                case DATA_TYPE_DOUBLE: {
                    db("Error. Cannot add number to string.");
                    exit(-1);
                    break;
                }
                case DATA_TYPE_STRING: {
                    ret.dataType = DATA_TYPE_STRING;
                    ret._stringData = this->_stringData + target._stringData;
                }
            }
            break;
        }
        default: {
            db("Error. Undefined data type.");
            exit(-1);
        }
    }
    db("returning from +:" << ret.dataType);
    return ret;
}

DataType DataType::operator-(const DataType& target) {
    DataType ret;
    switch (this->dataType) {
        case DATA_TYPE_DOUBLE: {
            switch (target.dataType) {
                case DATA_TYPE_DOUBLE: {
                    ret.dataType = DATA_TYPE_DOUBLE;
                    ret._doubledata = this->_doubledata - target._doubledata;
                    break;
                }
                case DATA_TYPE_STRING: {
                    db("Error. Invalid data type.");
                    exit(-1);
                    break;
                }
            }
            break;
        }
        case DATA_TYPE_STRING: {
            db("Error. No subtraction op supported for string type.");
            exit(-1);
            break;
        }
        default: {
            db("Error. Undefined data type.");
            exit(-1);
        }
    }
    return ret;
}

DataType DataType::operator*(const DataType& target) {
    DataType ret;
    switch (this->dataType) {
        case DATA_TYPE_DOUBLE: {
            switch (target.dataType) {
                case DATA_TYPE_DOUBLE: {
                    ret.dataType = DATA_TYPE_DOUBLE;
                    ret._doubledata = this->_doubledata * target._doubledata;
                    break;
                }
                case DATA_TYPE_STRING: {
                    db("Error. Invalid data type.");
                    exit(-1);
                    break;
                }
            }
            break;
        }
        case DATA_TYPE_STRING: {
            db("Error. No subtraction op supported for string type.");
            exit(-1);
            break;
        }
        default: {
            db("Error. Undefined data type.");
            exit(-1);
        }
    }
    return ret;
}

DataType DataType::operator/(const DataType& target) {
    DataType ret;
    switch (this->dataType) {
        case DATA_TYPE_DOUBLE: {
            switch (target.dataType) {
                case DATA_TYPE_DOUBLE: {
                    ret.dataType = DATA_TYPE_DOUBLE;
                    ret._doubledata = this->_doubledata / target._doubledata;
                    break;
                }
                case DATA_TYPE_STRING: {
                    db("Error. Invalid data type.");
                    exit(-1);
                    break;
                }
            }
            break;
        }
        case DATA_TYPE_STRING: {
            db("Error. No subtraction op supported for string type.");
            exit(-1);
            break;
        }
        default: {
            db("Error. Undefined data type.");
            exit(-1);
        }
    }
    return ret;
}

void DataType::operator=(const DataType& target) {
    this->dataType = target.dataType;
    switch (this->dataType) {
        case (DATA_TYPE_DOUBLE): {
            this->_doubledata = target._doubledata;
            break;
        }
        case (DATA_TYPE_STRING): {
            this->_stringData = target._stringData;
            break;
        }
        default: {
            db("Warning. Failed to assign from undefined data." << target._doubledata);
        }
    }
}

void DataType::operator=(const int target) {
    this->dataType = DATA_TYPE_DOUBLE;
    this->_doubledata = static_cast<double>(target);
}

void DataType::operator=(const double target) {
    this->dataType = DATA_TYPE_DOUBLE;
    this->_doubledata = target;
}

void DataType::operator=(const std::string& target) {
    this->dataType = DATA_TYPE_STRING;
    this->_stringData = target;
}

DataType DataType::operator<(const DataType& target) {
    DataType ret;
    switch (this->dataType) {
        case DATA_TYPE_DOUBLE: {
            switch (target.dataType) {
                case DATA_TYPE_DOUBLE: {
                    bool result = this->_doubledata < target._doubledata;
                    ret.dataType = DATA_TYPE_DOUBLE;
                    ret._doubledata = static_cast<double>(result);
                    break;
                }
                case DATA_TYPE_STRING: {
                    db("Error. Invalid data type in comparison <.");
                    exit(-1);
                    break;
                }
            }
            break;
        }
        case DATA_TYPE_STRING: {
            db("Error. String comparison not supported.");
            exit(-1);
            break;
        }
    }
    return ret;
}

DataType DataType::operator<=(const DataType& target) {
    DataType ret;
    switch (this->dataType) {
        case DATA_TYPE_DOUBLE: {
            switch (target.dataType) {
                case DATA_TYPE_DOUBLE: {
                    bool result = (this->_doubledata < target._doubledata) || FloatUtils::isEqual(this->_doubledata, target._doubledata);
                    ret.dataType = DATA_TYPE_DOUBLE;
                    ret._doubledata = static_cast<double>(result);
                    break;
                }
                case DATA_TYPE_STRING: {
                    db("Error. Invalid data type in comparison <.");
                    exit(-1);
                    break;
                }
            }
            break;
        }
        case DATA_TYPE_STRING: {
            db("Error. String comparison not supported.");
            exit(-1);
            break;
        }
    }
    return ret;
}

DataType DataType::operator>(const DataType& target) {
    DataType ret;
    switch (this->dataType) {
        case DATA_TYPE_DOUBLE: {
            switch (target.dataType) {
                case DATA_TYPE_DOUBLE: {
                    bool result = this->_doubledata > target._doubledata;
                    ret.dataType = DATA_TYPE_DOUBLE;
                    ret._doubledata = static_cast<double>(result);
                    break;
                }
                case DATA_TYPE_STRING: {
                    db("Error. Invalid data type in comparison >.");
                    exit(-1);
                    break;
                }
            }
            break;
        }
        case DATA_TYPE_STRING: {
            db("Error. String comparison not supported.");
            exit(-1);
            break;
        }
    }
    return ret;
}

DataType DataType::operator>=(const DataType& target) {
    DataType ret;
    switch (this->dataType) {
        case DATA_TYPE_DOUBLE: {
            switch (target.dataType) {
                case DATA_TYPE_DOUBLE: {
                    bool result = (this->_doubledata > target._doubledata) || FloatUtils::isEqual(this->_doubledata, target._doubledata);
                    ret.dataType = DATA_TYPE_DOUBLE;
                    ret._doubledata = static_cast<double>(result);
                    break;
                }
                case DATA_TYPE_STRING: {
                    db("Error. Invalid data type in comparison.");
                    exit(-1);
                    break;
                }
            }
            break;
        }
        case DATA_TYPE_STRING: {
            db("Error. String comparison not supported.");
            exit(-1);
            break;
        }
    }
    return ret;
}

DataType DataType::operator==(const DataType& target) {
    DataType ret;
    switch (this->dataType) {
        case DATA_TYPE_DOUBLE: {
            switch (target.dataType) {
                case DATA_TYPE_DOUBLE: {
                    bool result = FloatUtils::isEqual(this->_doubledata, target._doubledata);
                    ret.dataType = DATA_TYPE_DOUBLE;
                    ret._doubledata = static_cast<double>(result);
                    break;
                }
                case DATA_TYPE_STRING: {
                    db("Error. Invalid data type in comparison.");
                    exit(-1);
                    break;
                }
            }
            break;
        }
        case DATA_TYPE_STRING: {
            db("Error. String comparison not supported.");
            exit(-1);
            break;
        }
    }
    return ret;
}

bool DataType::operator==(const double target) {
    switch (this->dataType) {
        case DATA_TYPE_DOUBLE: {
            return FloatUtils::isEqual(this->_doubledata, target);
        }
        case DATA_TYPE_STRING: {
            db("Error. String comparison not supported.");
            exit(-1);
            return false;
        }
    }
    return false;
}

DataType DataType::operator!=(const DataType& target) {
    DataType ret;
    switch (this->dataType) {
        case DATA_TYPE_DOUBLE: {
            switch (target.dataType) {
                case DATA_TYPE_DOUBLE: {
                    bool result = !FloatUtils::isEqual(this->_doubledata, target._doubledata);
                    ret.dataType = DATA_TYPE_DOUBLE;
                    ret._doubledata = static_cast<double>(result);
                    break;
                }
                case DATA_TYPE_STRING: {
                    db("Error. Invalid data type in comparison.");
                    exit(-1);
                    break;
                }
            }
            break;
        }
        case DATA_TYPE_STRING: {
            db("Error. String comparison not supported.");
            exit(-1);
            break;
        }
    }
    return ret;
}

DataType DataType::operator&&(const DataType& target) {
    DataType ret;
    switch (this->dataType) {
        case DATA_TYPE_DOUBLE: {
            switch (target.dataType) {
                case DATA_TYPE_DOUBLE: {
                    bool result = static_cast<bool>(this->_doubledata) && static_cast<bool>(target._doubledata);
                    ret.dataType = DATA_TYPE_DOUBLE;
                    ret._doubledata = static_cast<double>(result);
                    break;
                }
                case DATA_TYPE_STRING: {
                    db("Error. Invalid data type in comparison.");
                    exit(-1);
                    break;
                }
            }
            break;
        }
        case DATA_TYPE_STRING: {
            db("Error. String comparison not supported.");
            exit(-1);
            break;
        }
    }
    return ret;
}

DataType DataType::operator||(const DataType& target) {
    DataType ret;
    switch (this->dataType) {
        case DATA_TYPE_DOUBLE: {
            switch (target.dataType) {
                case DATA_TYPE_DOUBLE: {
                    bool result = static_cast<bool>(this->_doubledata) || static_cast<bool>(target._doubledata);
                    ret.dataType = DATA_TYPE_DOUBLE;
                    ret._doubledata = static_cast<double>(result);
                    break;
                }
                case DATA_TYPE_STRING: {
                    db("Error. Invalid data type in comparison.");
                    exit(-1);
                    break;
                }
            }
            break;
        }
        case DATA_TYPE_STRING: {
            db("Error. String comparison not supported.");
            exit(-1);
            break;
        }
    }
    return ret;
}

std::ostream& operator<<(std::ostream& os, const DataType& data) {
    switch (data.dataType) {
        case DataType::DATA_TYPE_DOUBLE: {
            os << data._doubledata;
            break;
        }
        case DataType::DATA_TYPE_STRING: {
            os << data._stringData;
            break;
        }
    }
    return os;
}
