#ifndef __LIB_CONFIGURATION_HPP__
#define __LIB_CONFIGURATION_HPP__

#include <string>
#include <map>
#include <functional>
#include <vector>
#include <lib/include/types.hpp>
#include "appservice.hpp"
#include "data.hpp"

namespace lib
{
	class Configuration : public AppService
	{
	public:
		Configuration();
		virtual ~Configuration();
		Configuration &operator=(const Configuration &other) = delete;

		DataMap *configuration();
		DataMap *sharedData();

		bool loadConfiguration();
	private:

		DataMap m_rootNode;
	};
}

#endif
