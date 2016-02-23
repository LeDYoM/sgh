#include "address.hpp"

namespace lib
{
	namespace datap
	{

		Address::Address() :m_separator( "/" )
		{

		}

		Address::Address(const char *data)
			: Address{ std::string{ data } }
		{

		}

		Address::Address(const std::string &data)
			: Address{ }
		{
			std::string::size_type p = 0;
			std::string::size_type q;
			bool stay;
			do
			{
				q = data.find(m_separator, p);
				stay = (q != std::string::npos);
				if (stay)
				{
					m_data.emplace_back(data, p, q - p);
					p = q + 1;

				}
			} while (stay);
			m_data.emplace_back(data, p);
		}

		Address::~Address()
		{

		}

	}
}