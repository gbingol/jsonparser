#include <iostream>

#include "lexer.h"
#include "objects.hpp"


JSON::Value FromToken(const JSON::CToken& t)
{
	if(t.type() == t.BOOL)
		return JSON::Bool(std::get<bool>(t.value()));

	if(t.type() == t.STR)
		return JSON::String(std::get<std::string>(t.value()));
	
	if(t.type() == t.INT)
		return JSON::Int(std::get<int>(t.value()));

	if(t.type() == t.FLOAT)
		return JSON::Double(std::get<double>(t.value()));

	return {};
}


JSON::Value ParseObject(JSON::Lexer& lex)
{
	std::unordered_map<std::string, std::any> map;
	auto t = lex++;
	while(t.type() != t.BRACKET && std::get<std::string>(t.value())!="}")
	{
		auto keyToken = lex++;
		if(keyToken.type()!=keyToken.STR)
			throw std::exception("Invalid key in object");
	
		auto key = std::get<std::string>(keyToken.value());
		
		auto delimToken = lex++;
		if(delimToken.type() != delimToken.DELIM || std::get<std::string>(delimToken.value())!=":")
			throw std::exception("Object assignments require : sign");

		auto value = lex++;
		map[key] = FromToken(value);
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
		//std::cout << (int)t.type() << " " << t.value() << std::endl;
	}
}