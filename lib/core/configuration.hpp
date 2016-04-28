#ifndef __LIB_CONFIGURATION_HPP__
#define __LIB_CONFIGURATION_HPP__

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
		DataMap &configuration();
		void Init() override;

		void setDefaults(const DataMap &&defaults);
		DataValue &get(const str &cPath);

	private:
		DataMap m_rootNode;
		DataMap m_defaults;
	};
}

#endif
