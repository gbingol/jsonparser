#pragma once


#include <string>
#include <vector>


namespace JSON
{
	/* ***********   CGenericLex  *********************/

	class CToken
	{
	public:
		enum TYPE{ NUM = 0, ID, NONE, BOOL, BRACKET, DELIM, STR };

	public:
		CToken(TYPE type, std::string TokenValue) :	m_Type(type),m_Value(TokenValue){}
		CToken(TYPE type,char c) : CToken(type, std::string(1, c)) {}
		CToken(const CToken& other) = default;
		~CToken() = default;

		auto value() const { return m_Value; }
		TYPE type() const { return m_Type; }

	private:
		TYPE m_Type;

		//value of Token for any kind of Token, can be +,-, primary etc...
		std::string m_Value;
	};


	class CJSONLex
	{
	public:
		CJSONLex(const std::string& content)
		{
			m_Content = content;
			m_TokenPos = 0;

			Tokenize();
		}

		virtual ~CJSONLex() = default;

		auto next() {
			return (m_TokenPos < m_Tokens.size()) ? m_Tokens[m_TokenPos++] : nullptr;
		}

		auto prev() {
			return (m_TokenPos > 0) ? m_Tokens[m_TokenPos--] : nullptr;
		}

		auto at(size_t pos) const {
			return (pos < m_Tokens.size()) ? m_Tokens[pos] : nullptr;
		}

		void insert(size_t pos, CToken* token) {
			m_Tokens.insert(m_Tokens.begin() + pos, token);
		}

		size_t size() const {
			return m_Tokens.size();
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

		std::vector<CToken*> m_Tokens;

		std::string m_Content;
	};
}