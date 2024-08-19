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
		BasicType(T i=T{}):m_Data{i}{}
		~BasicType() = default;
		
		BasicType(const BasicType& other)
		{
			m_Data = other.m_Data;
		}

		BasicType(BasicType&& other) noexcept
		{
			m_Data = other.m_Data;
		}

		BasicType &operator=(const BasicType &rhs) = default;
		BasicType &operator=(BasicType&& rhs) noexcept = default;

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

		auto data() const{
			return m_Data;
		}

	private:
		T m_Data;
	};

	using Int = BasicType<int>;
	using Double = BasicType<double>;
	using String = BasicType<std::string>;
	using Bool = BasicType<bool>;

	class Value;

	struct Array
	{
		Array(const std::vector<std::shared_ptr<Value>>& d):m_Data{d}{}
		~Array() = default;

		Array(const Array &other) = default;

		Array(Array&& other) noexcept
		{
			m_Data = other.m_Data;
		}

		Array &operator=(const Array &rhs) = default;
		Array &operator=(Array &&rhs) noexcept = default;

		Array& operator=(const std::vector<std::shared_ptr<Value>>& rhs)
		{
			m_Data = rhs;
			return *this;
		}

		Array& operator=(std::vector<std::shared_ptr<Value>>&& rhs) noexcept
		{
			m_Data = rhs;
			return *this;
		}

		auto data() const{
			return m_Data;
		}

	private:
		std::vector<std::shared_ptr<Value>> m_Data;
	};


	struct Object
	{
		Object(const  std::unordered_map<std::string, std::shared_ptr<Value>>& d):m_Data{d}{}
		
		Object(const Object& other)
		{
			m_Data = other.m_Data;
		}

		Object(Object&& other) noexcept
		{
			m_Data = other.m_Data;
		}

		Object &operator=(const Object &rhs) = default;
		Object &operator=(Object &&rhs) noexcept = default;

		Object& operator=(const  std::unordered_map<std::string, std::shared_ptr<Value>>& rhs)
		{
			m_Data = rhs;
			return *this;
		}

		Object& operator=( std::unordered_map<std::string, std::shared_ptr<Value>>&& rhs) noexcept
		{
			m_Data = rhs;
			return *this;
		}

		~Object() = default;

		auto data() const{
			return m_Data;
		}

	protected:
		std::unordered_map<std::string, std::shared_ptr<Value>> m_Data;
	};


	class Value
	{
	public:
		Value() = default;
		Value(int i):m_Value{Int(i)}{}
		Value(double d):m_Value{Double(d)}{}
		Value(const std::string& s):m_Value{String(s)}{}
		Value(bool b):m_Value{Bool(b)}{}
		Value(const std::vector<std::shared_ptr<Value>>& v):m_Value{Array(v)}{}
		Value(const std::unordered_map<std::string, std::shared_ptr<Value>>& m):m_Value{Object(m)}{}

		Value(const Value& other)
		{
			std::visit([&](auto&& arg)
			{
				 using T = std::decay_t<decltype(arg)>;
				 if constexpr (std::is_same_v<T, Int>)
				 	m_Value = std::get<Int>(other.m_Value);
				 else if constexpr (std::is_same_v<T, Double>)
				 	m_Value = std::get<Double>(other.m_Value);
				 else if constexpr (std::is_same_v<T, String>)
				 	m_Value = std::get<String>(other.m_Value);
				else if constexpr (std::is_same_v<T, Bool>)
				 	m_Value = std::get<Bool>(other.m_Value);
				else if constexpr (std::is_same_v<T, Array>)
				 	m_Value = std::get<Array>(other.m_Value);
				else if constexpr (std::is_same_v<T, Object>)
				 	m_Value = std::get<Object>(other.m_Value);
				}, other.m_Value);
		}


		bool is_string() const { return std::holds_alternative<String>(m_Value); }
		bool is_double() const {  return std::holds_alternative<Double>(m_Value); }
		bool is_int() const {  return std::holds_alternative<Int>(m_Value); }
		bool is_bool() const {  return std::holds_alternative<Bool>(m_Value); }
		bool is_array() const {  return std::holds_alternative<Array>(m_Value); }
		bool is_object() const {  return std::holds_alternative<Object>(m_Value); }

		template<typename T>
		auto as() const 
		{ 
			return std::get<T>(m_Value).data(); 
		}

		auto as_string() const {return as<String>();};
		auto as_double() const { return as<Double>(); };
		auto as_int() const { return as<Int>(); };
		auto as_bool() const { return as<Bool>(); };
		auto as_array() const { return as<Array>(); };
		auto as_object() const { return as<Object>(); };

	private:
		//std::monostate for JSON's null
		using ValueType = std::variant<Int, Double, String, Bool, Array, Object>;
		ValueType m_Value;
	};

}