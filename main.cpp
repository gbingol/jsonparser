#include <iostream>
#include <assert.h>

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


JSON::Value ParseArray(JSON::Lexer& lex);

JSON::Value ParseObject(JSON::Lexer& lex)
{
	std::unordered_map<std::string, std::any> map;

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

		auto valTok = lex++;
		if(valTok.type() == t.BRACKET && std::get<std::string>(valTok.value())!="[")
		{
			map[key] = ParseArray(lex);
			lex++;
		}
		else
			map[key] = FromToken(valTok);
	}

	return JSON::Object(map);
}


JSON::Value ParseArray(JSON::Lexer& lex)
{
	std::vector<std::any> Arr;
	
	auto t = lex.cur();
	assert(t.type() == t.BRACKET && std::get<std::string>(t.value())=="[");

	while(lex.hasmore())
	{
		auto Token = lex++;
		if(Token.type() == Token.BRACKET && std::get<std::string>(Token.value())=="]")
			break;

		if(Token.type() == Token.DELIM && std::get<std::string>(Token.value())==",")
			continue;
		
		if(Token.type() == t.BRACKET && std::get<std::string>(Token.value())!="{")
		{
			Arr.push_back(ParseObject(lex));
			lex++;
		}
		else
			Arr.push_back(FromToken(Token));
	}

	return JSON::Array(Arr);
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
		auto v = std::get<JSON::Object>(ParseObject(lex));
		auto d = v.data();

		for(const auto e:d)
		{
			std::cout<<e.first<<std::endl;
		}
	}
}