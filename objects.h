#pragma once

#include <variant>
#include <string>
#include <vector>

namespace JSON
{
    
    struct ArrayType{};
    struct ObjectType{};

    using ValueType = std::variant<int, double, std::string, bool, ArrayType, ObjectType>;

    struct Array: ArrayType
    {
        Array() = default;
        Array& operator=(const std::vector<ValueType>& other);

    private:
        std::vector<ValueType> m_Data;
    };

}