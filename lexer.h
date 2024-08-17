#pragma once


#include <string>
#include <vector>


namespace JSONParser
{
	/* ***********   CGenericLex  *********************/

	class CToken
	{
	public:
		enum class TYPE {
			NUMBER = 0, IDENTIFIER, UNOP, BINOP, BRACKETS, DELIMITER,
			NEWLINE, ASSIGNMENT, STRING
		};

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


	class CGenericLex
	{
	public:
		CGenericLex(const std::string& tokenize)
		{
			m_Tokenize = tokenize;
			m_TokenPos = 0;

			Tokenize();
		}

		virtual ~CGenericLex() = default;

		auto next() {
			return (m_TokenPos < m_TokenList.size()) ? m_TokenList[m_TokenPos++] : nullptr;
		}

		auto prev() {
			return (m_TokenPos > 0) ? m_TokenList[m_TokenPos--] : nullptr;
		}

		auto at(size_t pos) const {
			return (pos < m_TokenList.size()) ? m_TokenList[pos] : nullptr;
		}

		void insert(size_t pos, CToken* token) {
			m_TokenList.insert(m_TokenList.begin() + pos, token);
		}

		size_t size() const {
			return m_TokenList.size();
		}

		auto operator++(int) {
			return m_TokenList[m_TokenPos++];
		}

		auto operator--(int) {
			return m_TokenList[m_TokenPos--];
		}

		auto begin() {
			return m_TokenList.begin();
		}

		auto end() {
			return m_TokenList.end();
		}

		bool hasmore() const {
			return m_TokenPos < m_TokenList.size();
		}

		const auto& data() const {
			return m_TokenList;
		}

	private:
		void Tokenize();

	private:
		size_t m_TokenPos; //tracking token's position in the vector

		std::vector<CToken*> m_TokenList;

		std::string m_Tokenize;
	};
}