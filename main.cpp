#include <iostream>
#include "json.h"

int main()
{
	JSON::JSON json(std::filesystem::path("testfiles/widgets.json"));
	auto v = json.Parse();
	std::cout << v;
}