#include "dataparser.hpp"
#include <cctype>

namespace lib
{
	namespace datap
	{
		DataParser::DataParser(const std::vector<std::string> &data)
			: m_data{ data }, m_cursor{ m_data }
		{
			while (!m_lastError && !m_cursor.eof())
			{

			}
		}

		sptr<DataObject> DataParser::readObject()
		{
			const DataParser::TokenData tokenData = nextToken();
			if (tokenData.isIdent())
			{
				TokenData temp = nextToken();
				if (!temp.isColon())
				{
					setError("Expected :");
					return nullptr;
				}
				TokenData temp2 = nextToken();

				if (temp2.isValidSymbol())
				{
					return DataObject::getNewLeaf(tokenData.data,temp2.data);
				}

			}
			else
			{
				setError("Expected identifier in readObject");
			}
		}

		const DataParser::TokenData DataParser::nextToken()
		{
			TokenData tokenData;
			while (!m_cursor.eof() && !m_lastError)
			{
				readBlanks();
				if (!m_cursor.eof() && !m_lastError)
				{
					char t{ m_cursor.current() };
					if (t == '"')
					{
						readIdent(tokenData);
					}
					else
					{
						tokenData.data = "" + t;
						if (!tokenData.isValidSymbol())
						{
							setError("Not valid symbol");
						}
					}
					return tokenData;
				}
			}
			return tokenData;
		}

		void DataParser::readBlanks()
		{
			bool cont{ true };

			while (cont)
			{
				cont = std::isspace(m_cursor.current()) || std::isblank(m_cursor.current());
				++m_cursor;
			}
		}

		void DataParser::setError(const std::string &message)
		{
			m_lastError = sptr<ParserError>(new ParserError{ m_cursor, message });
		}

		void DataParser::readIdent(TokenData &out)
		{
			if (m_cursor.current() != '"')
			{
				setError("Expected:'\"'");
			}

			while ((++m_cursor).current() != '"')
			{
				out.data += m_cursor.current();
			}

			++m_cursor;
		}
	}
}
