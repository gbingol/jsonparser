#pragma once

#include <string>
#include <filesystem>

#include "objects.h"
#include "lexer.h"


namespace JSON
{
	class JSON
	{
	public:
		JSON(const std::string& s):m_Content{s} {}
		JSON(std::filesystem::path path);

		//1st: id (converted to uppercase), 2nd: value
		Value Parse();

	private:
		Value ParseArray(Lexer& lex);
		Value ParseObject(Lexer &lex);
		Value FromObject(Lexer &lex);

	private:
		std::string m_Content;
	};
}