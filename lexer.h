#pragma once

#include <string>
#include <vector>
#include <optional>
#include <variant>


namespace JSON
{
	class CToken
	{
	public:
		enum TYPE{ INT = 0, FLOAT, ID, NONE, BOOL, BRACKET, DELIM, STR };
		using DTYPE = std::variant<int, double, bool, std::string>;
	public:
		CToken(TYPE type, DTYPE TokenValue = {}) :	m_Type(type),m_Value(TokenValue){}

		auto value() const { return m_Value; }
		TYPE type() const { return m_Type; }

	private:
		TYPE m_Type;

		//value of Token for any kind of Token, can be +,-, primary etc...
		DTYPE m_Value;
	};


	class Lexer
	{
	public:
		Lexer(std::string_view JSONText)
		{
			m_TokenPos = 0;
			Tokenize(JSONText);
		}

		virtual ~Lexer() = default;

		size_t size() const {
			return m_Tokens.size();
		}

		auto cur() const{
			return m_Tokens[m_TokenPos];
		}

		//post-increment
		auto operator++(int) {
			return m_Tokens[m_TokenPos++];
		}

		//post-decrement
		auto operator--(int) {
			return m_Tokens[m_TokenPos--];
		}

		//move lexical position forward or backwards with given step size
		void move(int step=1)
		{
			m_TokenPos += step;
			if(m_TokenPos<0 || m_TokenPos>size())
				throw "Invalid step size.";
		}

		auto begin() {
			return m_Tokens.begin();
		}

		auto end() {
			return m_Tokens.end();
		}


	private:
		void Tokenize(std::string_view JSONText);

	private:
		//tracking token's position in the vector
		size_t m_TokenPos;

		//list of tokens
		std::vector<CToken> m_Tokens;
	};
}