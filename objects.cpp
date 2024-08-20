#include "objects.h"

#include <sstream>

namespace JSON
{
	Array::Array(const std::vector<Value> &d)
	{
		m_Data = d;
	}

	Array &Array::operator=(const std::vector<Value> &rhs)
	{
		m_Data = rhs;
		return *this;
	}

	Array &Array::operator=(std::vector<Value> &&rhs) noexcept
	{
		m_Data = rhs;
		return *this;
	}

    void Array::push_back(const Value &v)
    {
		m_Data.push_back(v);
    }

    std::ostream &operator<<(std::ostream &os, const Array &arr)
	{
		os << "[";
		for (size_t i = 0; i < arr.m_Data.size() - 1; ++i)
		{
			auto e = arr.m_Data[i];
			os << e << ",";
		}
		os << *arr.m_Data.rbegin();
		os << "]";

		return os;
	}


	/**************************************************** */

	Object::Object(const std::unordered_map<std::string, Value> &d)
	{
		m_Data = d;
	}

	Object &Object::operator=(const std::unordered_map<std::string, Value> &rhs)
	{
		m_Data = rhs;
		return *this;
	}

	Object &Object::operator=(std::unordered_map<std::string, Value> &&rhs) noexcept
	{
		m_Data = rhs;
		return *this;
	}

	std::ostream &operator<<(std::ostream &os, const Object &obj)
	{
		auto Last = (--obj.m_Data.end());
		os << "{";
		for (auto iter = std::begin(obj.m_Data); iter != std::end(obj.m_Data); ++iter)
		{
			os << "\"" << (*iter).first << "\""; //key
			os << ":";
			os << (*iter).second;

			if(iter != Last)
				os << ",";
		}
		os << "}";

		return os;
	}


	/************************************** */

	std::ostream &operator<<(std::ostream &os, const Value &v)
	{
		if(v.is_array())
			os << v.as_Array();
		else if(v.is_object())
			os << v.as_Object();
		else if(v.is_bool())
			os << v.as_bool();
		else if(v.is_int())
			os << v.as_int();
		else if(v.is_double())
			os << v.as_double();
		else if(v.is_string())
			os << "\"" << v.as_string() << "\"";
		else if(v.is_null())
			os << "null";

		return os;
	}

}