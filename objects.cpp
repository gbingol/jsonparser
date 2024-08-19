#include "objects.h"

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


	std::ostream &operator<<(std::ostream &os, const Array &arr)
	{
		os << arr.print();
		return os;
	}

	std::string Array::print() const
	{
		return std::string();
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

}