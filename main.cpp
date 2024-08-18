#include <iostream>

#include "lexer.h"
#include "objects.hpp"


JSON::Value FromToken(const JSON::CToken& t)
{
	if(t.type() == t.BOOL)
		return JSON::Bool(t.value() == "true" ? true : false);

	if(t.type() == t.STR)
		return JSON::String(t.value());
}


JSON::Value ParseObject(JSON::Lexer& lex)
{
	std::unordered_map<std::string, std::any> map;
	auto t = lex++;
	while(t.value()!="}")
	{
		auto key = lex++;
		lex++;
		auto value = lex++;
	}

	return JSON::Object(map);
}



int main()
{
	std::string s = "{ \
	\"guid\":\"37e82d6f-1aeb-409f-9395-bb78356e922c\", \
	\"extname\":\"Charts\", \
	\"developer\": \"PEBytes\", \
	\"readme\":\"readme/readme.html\", \
	\"short_desc\":\"Plot Charts\", \
	}";

	JSON::Lexer lex(s);
	while(lex.hasmore())
	{
		auto t = lex++;
		std::cout << (int)t.type() << " " << t.value() << std::endl;
	}
}