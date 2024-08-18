#pragma once

#include <variant>
#include <string>
#include <vector>
#include <unordered_map>
#include <any>

namespace JSON
{

    template<typename T>
    struct BasicType 
    {
        BasicType() = default;
        BasicType(T i):m_Data{i}{}
       
        BasicType(const BasicType& other)
        {
            m_Data = other.m_Data;
        }

        BasicType(BasicType&& other) noexcept
        {
            m_Data = other.m_Data;
        }

        BasicType& operator=(const T& rhs)
        {
            m_Data = rhs;
            return *this;
        }

        BasicType& operator=(T&& rhs) noexcept
        {
            m_Data = rhs;
            return *this;
        }

        ~BasicType() = default;

    protected:
        T m_Data;
    };

	using Int = BasicType<int>;
	using Double = BasicType<double>;
	using String = BasicType<std::string>;
	using Bool = BasicType<bool>;
	
   

    struct Array
	{
		Array(const std::vector<std::any>& d):m_Data{d}{}
       
        Array(const Array& other)
        {
            m_Data = other.m_Data;
        }

        Array(Array&& other) noexcept
        {
            m_Data = other.m_Data;
        }

        Array& operator=(const std::vector<std::any>& rhs)
        {
            m_Data = rhs;
            return *this;
        }

        Array& operator=(std::vector<std::any>&& rhs) noexcept
        {
            m_Data = rhs;
            return *this;
        }

        ~Array() = default;

    protected:
        std::vector<std::any> m_Data;
	};


	struct Object
	{
		Object(const  std::unordered_map<std::string, std::any>& d):m_Data{d}{}
       
        Object(const Object& other)
        {
            m_Data = other.m_Data;
        }

        Object(Object&& other) noexcept
        {
            m_Data = other.m_Data;
        }

        Object& operator=(const  std::unordered_map<std::string, std::any>& rhs)
        {
            m_Data = rhs;
            return *this;
        }

        Object& operator=( std::unordered_map<std::string, std::any>&& rhs) noexcept
        {
            m_Data = rhs;
            return *this;
        }

        ~Object() = default;

        auto data() const{
            return m_Data;
        }

    protected:
        std::unordered_map<std::string, std::any> m_Data;
	};



    template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
    template<class... Ts> overload(Ts...) -> overload<Ts...>;

    class Value
    {
    public:
        Value() = default;
        Value(int i):m_Value{Int(i)}{}
        Value(double d):m_Value{Double(d)}{}
        Value(const std::string& s):m_Value{String(s)}{}
        Value(bool b):m_Value{Bool(b)}{}
        Value(const std::vector<std::any>& v):m_Value{Array(v)}{}
        Value(const std::unordered_map<std::string, std::any>& m):m_Value{Object(m)}{}

        Value(const Value& other)
        {
           std::visit(overload{
            [&](Int )       { m_Value = std::get<Int>(other.m_Value); },
            [&](Double& )   {  m_Value = std::get<Double>(other.m_Value); },
            [&](String& )   { m_Value = std::get<String>(other.m_Value); },
            [&](Bool& ) { m_Value = std::get<Bool>(other.m_Value); },
            [&](Array& ) { m_Value = std::get<Array>(other.m_Value); }
            }, other.m_Value);
        }

    private:
        //std::monostate for JSON's null
        using ValueType = std::variant<Int, Double, String, Bool, Array, Object>;
        ValueType m_Value;
    };

    

}