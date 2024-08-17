#include "lexer.h"
#include <stdexcept>


namespace JSONParser
{
	void CGenericLex::Tokenize()
	{
		std::string tokenStr;
		size_t len = m_Tokenize.length();

		if (m_Tokenize.empty()) 
			throw std::exception("Empty string cannot be tokenized.");

		for (size_t index = 0; index < len; ++index)
		{
			char c = m_Tokenize[index];

			if (!isascii(c))
				continue;

			else if (c == 0 || c == '\0')
				break;

			else if ((c == ' ' || c == '\t'))
				continue;

			else if (isdigit(c))
			{
				size_t Pos = index;
				char* pEnd;
				auto SubStr = m_Tokenize.substr(index);

				auto Num = std::strtod(SubStr.c_str(), &pEnd);
				auto Length = std::distance(const_cast<char*>(SubStr.c_str()), pEnd);

				index += Length - 1;

				m_TokenList.push_back(new CToken(CToken::TYPE::NUMBER, m_Tokenize.substr(Pos, Length)));
			}

			//decimal equivalent in ASCII is 39
			else if (c == '\"' || c == '\'')
			{
				char Character = c == '\"' ? '\"' : '\'';

				tokenStr += c;

				while ((c = m_Tokenize[++index]) != Character && index < m_Tokenize.length())
					tokenStr = tokenStr + c;

				if (index == m_Tokenize.length())
					throw std::exception("Parse error while searching for \" or \'");

				tokenStr += c;

				m_TokenList.push_back(new CToken(CToken::TYPE::STRING, tokenStr));
			}

			else if (c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}')
				m_TokenList.push_back(new CToken(CToken::TYPE::BRACKETS, c));


			else if (c == '-' || c == '+' || c == '/' || c == '*' || c == '%' || c == '^' || c == '&' || c == '|' || c == '>' || c == '<')
				m_TokenList.push_back(new CToken(CToken::TYPE::BINOP, c));


			else if (c == '.' || c == ';' || c == ',' || c == '#' || c == '!' || c == ':' || c == '~')
				m_TokenList.push_back(new CToken(CToken::TYPE::DELIMITER, c));

			else if (c == '=')
				m_TokenList.push_back(new CToken(CToken::TYPE::ASSIGNMENT, c));


			else if (isalpha(c) || c == '_')
			{
				tokenStr += c;

				c = m_Tokenize[++index];

				while (isascii(c) && ((bool)std::isalnum(c) || c == '_'))
				{
					tokenStr += c;
					c = m_Tokenize[++index];
				}

				index--;
				m_TokenList.push_back(new CToken(CToken::TYPE::IDENTIFIER, tokenStr));
			}

			tokenStr.clear();
		}
	}

}