#include <iostream>

#include "lexer.h"
#include "objects.h"

int main()
{
	std::string s = "{ \
	\"guid\":\"37e82d6f-1aeb-409f-9395-bb78356e922c\", \
	\"extname\":\"Charts\", \
	\"developer\": \"PEBytes\", \
	\"readme\":\"readme/readme.html\", \
	\"short_desc\":\"Plot Charts\", \
	}";

	JSON::CJSONLex lex(s);
	auto tokens = lex.data();
	for(auto t: tokens)
	{
		std::cout << (int)t.type() << " " << t.value() << std::endl;
	}
}