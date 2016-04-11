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
		static const str staticTypeName() { return "Configuration"; }

		DataMap *configuration();
		DataMap *sharedData();

		void Init() override;

		std::vector<str> loadFile(const std::string &file);

	private:

		DataMap m_rootNode;
	};
}

#endif
