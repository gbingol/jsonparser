#include <iostream>
#include "json.h"

int main()
{
	JSON::JSON json(std::filesystem::path("testfiles/widgets.json"));
	JSON::Error err;
	auto v = json.Parse(err);

	if(!err.failed)
		std::cout << v;
}