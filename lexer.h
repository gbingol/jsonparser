#pragma once


#include <string>
#include <vector>
#include <optional>
#include <variant>


namespace JSON
{
	/* ***********   CGenericLex  *********************/

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
		Lexer(const std::string& content)
		{
			m_Content = content;
			m_TokenPos = 0;

			Tokenize();
		}

		virtual ~Lexer() = default;

		std::optional<CToken> next() {
			if (m_TokenPos < m_Tokens.size()) 
				return m_Tokens[m_TokenPos++];
			return {};
		}

		std::optional<CToken> prev() {
			if (m_TokenPos > 0) 
				return m_Tokens[m_TokenPos--];
			return {};
		}

		std::optional<CToken> at(size_t pos) const {
			if (pos < m_Tokens.size())
				return m_Tokens[pos];
			return {};
		}

		void insert(size_t pos, CToken token) {
			m_Tokens.insert(m_Tokens.begin() + pos, token);
		}

		size_t size() const {
			return m_Tokens.size();
		}

		auto cur() const{
			return m_Tokens[m_TokenPos];
		}

		auto operator++(int) {
			return m_Tokens[m_TokenPos++];
		}

		auto operator--(int) {
			return m_Tokens[m_TokenPos--];
		}

		auto begin() {
			return m_Tokens.begin();
		}

		auto end() {
			return m_Tokens.end();
		}

		bool hasmore() const {
			return m_TokenPos < m_Tokens.size();
		}

		const auto& data() const {
			return m_Tokens;
		}

	private:
		void Tokenize();

	private:
		size_t m_TokenPos; //tracking token's position in the vector

		std::vector<CToken> m_Tokens;

		std::string m_Content;
	};
}