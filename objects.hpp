#pragma once

#include <variant>
#include <string>
#include <vector>
#include <unordered_map>
#include <any>

namespace JSON
{
    
    struct CType
	{
		virtual bool isString() const { return false; }
		virtual bool isDouble() const { return false; }
		virtual bool isBool() const { return false; }
		virtual bool isArray() const { return false; }
		virtual bool isObject() const { return false; }
	};

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

		constexpr bool isInteger() const
		{
			if constexpr (std::is_same<T, int>::value)
				return true;
			return false;
		}

		constexpr bool isDouble() const
		{
			if constexpr (std::is_same<T, double>::value)
				return true;
			return false;
		}

		constexpr bool isString() const
		{
			if constexpr (std::is_same<T, std::string>::value)
				return true;
			return false;
		}

		constexpr bool isBool() const
		{
			if constexpr (std::is_same<T, bool>::value)
				return true;
			return false;
		}

    protected:
        T m_Data;
    };

	using Int = BasicType<int>;
	using Double = BasicType<double>;
	using String = BasicType<std::string>;
	using Bool = BasicType<bool>;
	
   

    struct Array : CType
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

        Array operator=(const std::vector<std::any>& rhs)
        {
            m_Data = rhs;
            return *this;
        }

        Array operator=(std::vector<std::any>&& rhs) noexcept
        {
            m_Data = rhs;
            return *this;
        }

		bool isArray() const override { return true; }

    protected:
        std::vector<std::any> m_Data;
	};


	struct Object : CType
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

        Object operator=(const  std::unordered_map<std::string, std::any>& rhs)
        {
            m_Data = rhs;
            return *this;
        }

        Object operator=( std::unordered_map<std::string, std::any>&& rhs) noexcept
        {
            m_Data = rhs;
            return *this;
        }

		bool isObject() const override { return true; }

        auto data() const{
            return m_Data;
        }

    protected:
        std::unordered_map<std::string, std::any> m_Data;
	};


    //std::monostate for JSON's null
    using Value = std::variant<Int, Double, String, Bool, Array, Object>;

}