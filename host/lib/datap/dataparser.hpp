#ifndef LIB_DATAP_DATAPARSER_HPP
#define LIB_DATAP_DATAPARSER_HPP

#include <vector>
#include <string>
#include <lib/include/types.hpp>
#include "dataobject.hpp"

namespace lib
{
	namespace datap
	{
		class DataParser
		{
			enum class State
			{
				Free,
				ReadingIdent,
				ReadingSeparator,
				ReadingObject
			};
			class Cursor
			{
			public:
				u32 currentLine{ 0 };
				u32 currentRow{ 0 };
				const std::vector<std::string> &m_data;
				Cursor(const std::vector<std::string> &data) : m_data{ data } {}
				Cursor &operator=(const Cursor &) = delete;
				bool eof() const { return currentLine > m_data.size(); }
				const char &current() const { return m_data[currentLine][currentRow]; }
				void advance()
				{
					if (++currentRow >= m_data[currentLine].size()) { ++currentLine; currentRow = 0; }
				}
				Cursor &operator++() { advance(); return *this; }
			};

			class ParserError
			{
			public:
				Cursor cursor;
				const std::string message;
				ParserError(Cursor &cursor_, const std::string &message_) : cursor{ cursor_ }, message( message_ ) {}
			};

			class TokenData
			{
			public:
				std::string data;
				bool isColon() const { return data.size() == 1 && data[0] == ':'; }
				bool isOpenBrackets() const { return data.size() == 1 && data[0] == '{'; }
				bool isCloseBrackets() const { return data.size() == 1 && data[0] == '}'; }
				bool isIdent() const { return data.size() > 0 && !isColon() && !isOpenBrackets() && !isCloseBrackets(); }
				bool isValidSymbol() const { return data.size() == 1 && (isColon() || isOpenBrackets() || isCloseBrackets()); }
			};

			DataParser(const std::vector<std::string> &);

		private:
			sptr<ParserError> m_lastError;
			State m_state{ State::Free };
			const std::vector<std::string> &m_data;
			Cursor m_cursor;
			sptr<DataObject> readObject();
			const TokenData nextToken();
			void readBlanks();
			void setError(const std::string &message);
			void readIdent(TokenData &out);
		};
	}
}

#endif

