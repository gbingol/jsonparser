#pragma once

#include <variant>
#include <string>
#include <vector>
#include <unordered_map>

namespace JSON
{
    
    struct CType{};

    template<typename T>
    struct BasicType : CType
    {
        BasicType(T i =T{}):m_Data{i}{}
       
        BasicType(const BasicType& other)
        {
            m_Data = other.m_Data;
        }

        BasicType(BasicType&& other) noexcept
        {
            m_Data = other.m_Data;
        }

        BasicType operator=(const T& rhs)
        {
            m_Data = rhs;
            return *this;
        }

        BasicType operator=(T&& rhs) noexcept
        {
            m_Data = rhs;
            return *this;
        }

    protected:
        T m_Data;
    };


    struct Int : BasicType<int> { };
    struct Double : BasicType<double>{};
    struct String : BasicType<std::string>{};
    struct Bool : BasicType<bool>{};
   
    struct Array : BasicType<std::vector<CType>>{};
    struct Object : BasicType<std::unordered_map<std::string, CType>>{};

    //std::monostate for JSON's null
    using Value = std::variant<Int, Double, String, Bool, Array, Object>;

}