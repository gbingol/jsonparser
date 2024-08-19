#include <iostream>
#include <assert.h>

#include "lexer.h"
#include "objects.hpp"


JSON::Value ParseArray(JSON::Lexer& lex);
JSON::Value ParseObject(JSON::Lexer &lex);


JSON::Value FromToken(JSON::Lexer& lex)
{
	auto t = lex.cur();
	if(t.type() == t.BOOL)
		return std::get<bool>(t.value());

	if(t.type() == t.STR)
		return std::get<std::string>(t.value());
	
	if(t.type() == t.INT)
		return std::get<int>(t.value());

	if(t.type() == t.FLOAT)
		return std::get<double>(t.value());
	
	if(t.type() == t.BRACKET && std::get<std::string>(t.value())!="[")
	{
		lex++;
		return ParseArray(lex);
	}

	if(t.type() == t.BRACKET && std::get<std::string>(t.value())!="[")
	{
		lex++;
		return ParseObject(lex);
	}

	return {};
}



JSON::Value ParseObject(JSON::Lexer& lex)
{
	std::unordered_map<std::string, std::shared_ptr<JSON::Value>> map;

	auto t = lex.cur();
	assert(t.type() == t.BRACKET && std::get<std::string>(t.value())=="{");
	lex++;
	while(lex.hasmore())
	{
		auto Token = lex++;
		if(Token.type() == Token.BRACKET && std::get<std::string>(Token.value())=="}")
			break;

		if(Token.type() == Token.DELIM && std::get<std::string>(Token.value())==",")
			continue;

		if(Token.type()!=Token.STR)
			throw std::exception("Invalid key in object");
	
		auto key = std::get<std::string>(Token.value());
		
		auto ColTok = lex++;
		if(ColTok.type() != ColTok.DELIM || std::get<std::string>(ColTok.value())!=":")
			throw std::exception("Object assignments require : sign");

		auto valTok = lex.cur();
		map[key] = std::make_shared<JSON::Value>(FromToken(lex));
		lex++;
	}

	return map;
}


JSON::Value ParseArray(JSON::Lexer& lex)
{
	std::vector<std::shared_ptr<JSON::Value>> Arr;
	
	auto t = lex.cur();
	assert(t.type() == t.BRACKET && std::get<std::string>(t.value())=="[");

	while(lex.hasmore())
	{
		auto Token = lex.cur();
		if(Token.type() == Token.BRACKET && std::get<std::string>(Token.value())=="]")
			break;

		if(Token.type() == Token.DELIM && std::get<std::string>(Token.value())==",")
			continue;
		
		Arr.push_back(std::make_shared<JSON::Value>(FromToken(lex)));
		lex++;
	}

	return Arr;
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
	auto t = lex.cur();

	if(t.type() == t.BRACKET && std::get<std::string>(t.value())=="{")
	{
		auto v = ParseObject(lex);
		if(v.is_object())
		{
			auto d = v.as_object();
			for(const auto e:d)
			{
				std::cout << e.first;
				auto v = *e.second;
				
				if(v.is_string())
					std::cout << v.as_string() << std::endl;
			}
		}
	}
}