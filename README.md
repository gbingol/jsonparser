## JSON Parser

This is a portable, easy to integrate (a single header and a cpp file) library which parses JSON text/file and serializes C++ data to JSON text. Its design was inspired by [Boost::JSON](https://www.boost.org/doc/libs/1_86_0/libs/json/doc/html/index.html) and has been tested with the JSON files in the `testfiles` folder.

It contains only 7 interface objects: 
1. Value (Any JSON value, basically any of the following),
2. Int (integers),
3. Double (floats),
4. String (strings), 
5. Bool (true or false), 
6. Array (Value array), 
7. Object (key, value pairs)



## Requirements

 Requires C++17 or higher.


&nbsp;


## Use

Designed for simplicity.



```C++
#include <iostream>
#include "json.h"

int main()
{
    //constructor can be either a std::filesystem::path or UTF8 std::string
	JSON::JSON json(std::filesystem::path("testfiles/widgets.json"));

    //v is a JSON value
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
It should be noted that none of the above-listed `as_` methods checks the type, therefore possibly can cause a crash if the value does not match. Therefore, use `is_` checks before attempting to extract corresponding C++ values.