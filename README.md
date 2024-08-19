## JSON Parser

This is a portable C++ library which provides containers and algorithms that implement JSON data-interchange format. It focuses on a common and popular use-case: parsing and serializing to and from a container.


Its design is inspired by Boost::JSON and among others successfully passed all the tests with the files in the jsonfiles folder.


## Requirements

 Requires C++17 or higher.

 &nbsp;

## Interface Objects

1. Value (Any JSON value, basically any of the following),
2. Int (int),
3. Double (double),
4. String (const char* or std::string), 
5. Bool (bool), 
6. Array (std::vector<Value>), 
7. Object (std::unordered_map<std::string, Value>)


&nbsp;


## Use

Designed for simplicity.



```C++
#include <iostream>
#include "json.h"

int main()
{
    //constructor can be either a std::filesystem::path or UTF8 std::string
	JSON::JSON json(std::filesystem::path("jsonfiles/widgets.json"));

    //a JSON value
	auto v = json.Parse(); 

    //write to output stream
	std::cout << v; 
}
```

&nbsp;

The `Value` can be tested with the following methods:

```C++
bool is_null() const;
bool is_string() const;
bool is_double() const;
bool is_int() const; 
bool is_bool() const;
bool is_array() const; 
bool is_object() const;
```

The equivalent C++ data-types can be extracted simply using the following:

```C++
auto as_string() const; //std::string
auto as_double() const; //double
auto as_int() const; //int
auto as_bool() const; //bool
auto as_array() const; //std::vector<Value>
auto as_object() const; //std::unordered_map<std::string, Value>

```
It should be noted that any of the above-listed `as_` methods does not perform a further type check.