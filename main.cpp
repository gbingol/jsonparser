#include <iostream>
#include <assert.h>

#include "json.h"



int main()
{

	JSON::JSON json(std::filesystem::path("jsonfiles/manifest.json"));
	auto v = json.Parse();
	std::cout << v;

	
}