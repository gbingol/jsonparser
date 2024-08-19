#include "json.h"

#include <assert.h>
#include <locale>
#include <codecvt>
#include <fstream>
#include <unordered_map>



namespace JSON
{
	JSON::JSON(std::filesystem::path path)
	{
		if (!std::filesystem::exists(path))
			throw std::exception("File does not exist");

		std::wifstream file(path, std::ios::in);
		if (!file.is_open())  
			throw std::exception("Failed to open file");

		file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));
	
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		for (std::wstring Line; std::getline(file, Line);)
			m_Content.append(converter.to_bytes(Line));

		file.close();
	}


	Value JSON::Parse()
	{
		Lexer lex(m_Content);
		auto t = lex.cur();

		if(t.type() == t.BRACKET)
		{
			if(std::get<std::string>(t.value())=="{")
				return ParseObject(lex);
			
			if(std::get<std::string>(t.value())=="[")
				return ParseArray(lex);
		}

		return Value();
	}


	Value JSON::FromObject(Lexer& lex)
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
		
		if(t.type() == t.BRACKET && std::get<std::string>(t.value())=="[")
		{
			return ParseArray(lex);
		}

		if(t.type() == t.BRACKET && std::get<std::string>(t.value())=="{")
		{
			lex++;
			return ParseObject(lex);
		}

		return {};
	}



	Value JSON::ParseObject(Lexer& lex)
	{
		std::unordered_map<std::string, Value> map;

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
			map[key] = FromObject(lex);
			lex++;
		}

		return map;
	}


	Value JSON::ParseArray(Lexer& lex)
	{
		std::vector<Value> Arr;
		
		auto t = lex.cur();
		assert(t.type() == t.BRACKET && std::get<std::string>(t.value())=="[");

		while(lex.hasmore())
		{
			lex++;
			auto Token = lex.cur();
			if(Token.type() == Token.BRACKET && std::get<std::string>(Token.value())=="]")
				break;

			if(Token.type() == Token.DELIM && std::get<std::string>(Token.value())==",")
				continue;
			
			Arr.push_back(FromObject(lex));
		}

		return Arr;
	}

}