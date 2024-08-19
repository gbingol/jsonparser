#include <iostream>
#include <assert.h>

#include "json.h"



int main()
{
	std::string s = "{ \
	\"guid\":\"37e82d6f-1aeb-409f-9395-bb78356e922c\", \
	\"extname\":\"Charts\", \
	\"developer\": \"PEBytes\", \
	\"readme\":\"readme/readme.html\", \
	\"short_desc\":\"Plot Charts\", \
	}";

	JSON::JSON json(std::filesystem::path("js_history.json"));
	auto v = json.Parse();

	if(v.is_object())
	{
		auto d = v.as_object();
		for(const auto e:d)
		{
			std::cout << e.first << " ";
			auto v = e.second;	
			if(v.is_string())
				std::cout << v.as_string() << std::endl;
		}
	}

	if(v.is_array())
	{
		auto arr = v.as_array();
		for(const auto e: arr)
		{
			if(e.is_array())
			{
				
			}
			if(e.is_string())
				std::cout << e.as_string() << std::endl;
		}
	}
}