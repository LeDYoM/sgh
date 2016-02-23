#ifndef LIB_DATAP_ADDRESS_HPP
#define LIB_DATAP_ADDRESS_HPP

#include <string>
#include <vector>

namespace lib
{
	namespace datap
	{
		class Address
		{
		public:
			Address();
			Address(const char *data);
			Address(const std::string &data);
			Address(const Address &right) = default;
			Address(Address &&right) : m_data( std::move(right.m_data) ), m_separator( std::move(right.m_separator) ) {}
			~Address();
		private:
			std::vector<std::string> m_data;
			std::string m_separator;
		};
	}
}

#endif

