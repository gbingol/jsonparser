#pragma once

#include <variant>
#include <string>
#include <vector>
#include <unordered_map>

namespace JSON
{
    
    struct CType{};

    template<typename T>
    class BasicType : public CType
    {
        BasicType(T i):m_Data{i}{}
       
        BasicType(const BasicType& other)
        {
            m_Data = other.m_Data;
        }

        BasicType(BasicType&& other) noexcept
        {
            m_Data = other.m_Data;
        }

        T& operator=(const T& rhs)
        {
            m_Data = rhs;
            return *this;
        }

        T& operator=(T&& rhs) noexcept
        {
            m_Data = rhs;
            return *this;
        }

    protected:
        T m_Data;
    };


    class Int : public BasicType<int> { };
    class Double : public  BasicType<double>{};
    class String : public  BasicType<std::string>{};
    class Bool : public  BasicType<bool>{};
   
    class Array : public  BasicType<std::vector<CType>>{};
    class Object : public  BasicType<std::unordered_map<std::string, CType>>{};

    //std::monostate for JSON's null
    using Value = std::variant<Int, Double, String, Bool, Array, Object>;

}