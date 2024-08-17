#include "objects.h"


namespace JSON
{
    Array &Array::operator=(const std::vector<ValueType> &other)
    {
        m_Data = other;
        return *this;
    }

}