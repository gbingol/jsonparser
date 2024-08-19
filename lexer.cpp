#include "lexer.h"
#include <stdexcept>


namespace JSON
{
	void Lexer::Tokenize()
	{
		std::string tokenStr;
		size_t len = m_Text.length();

		if (m_Text.empty()) 
			throw std::exception("Empty string cannot be tokenized.");

		for (size_t index = 0; index < len; ++index)
		{
			char c = m_Text[index];

			if (c == 0 || c == '\0')
				break;

			else if (c == ' ' || c == '\t')
				continue;

			else if (isdigit(c))
			{
				char* pEnd;
				auto SubStr = m_Text.substr(index);

				auto Num = std::strtod(SubStr.c_str(), &pEnd);
				auto Length = std::distance(const_cast<char*>(SubStr.c_str()), pEnd);

				index += Length - 1;

				if(int(Num) == Num)
					m_Tokens.emplace_back(CToken::INT, (int)Num);
				else
					m_Tokens.emplace_back(CToken::FLOAT, Num);
			}

			//decimal equivalent in ASCII is 39
			else if (c == '\"' || c == '\'')
			{
				char Search = c == '\"' ? '\"' : '\'';

				while (	(c = m_Text[++index]) != Search && index < len)
					tokenStr = tokenStr + c;

				if (index == m_Text.length())
					throw std::exception("Parse error while searching for \" or \'");

				m_Tokens.emplace_back(CToken::STR, tokenStr);
			}

			else if (c == '[' || c == ']' || c == '{' || c == '}')
				m_Tokens.emplace_back(CToken::BRACKET, std::string(1, c));

			else if (c == ',' || c == ':' )
				m_Tokens.emplace_back(CToken::DELIM, std::string(1, c));

			else if (isalpha(c) || c == '_') 
			{
				tokenStr += c;

				c = m_Text[++index];
				while (std::isalnum(c) || c == '_') {
					tokenStr += c;
					c = m_Text[++index];
				}
				index--;

				if(tokenStr == "true" || tokenStr == "false")
					m_Tokens.emplace_back(CToken::BOOL, tokenStr == "true" ? true : false);

				else if(tokenStr == "null")
					m_Tokens.emplace_back(CToken::NONE);

				else
					m_Tokens.emplace_back(CToken::ID, tokenStr);
			}

			tokenStr.clear();
		}
	}

}