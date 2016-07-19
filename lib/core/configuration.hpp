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

		DataValue get(const str &cPath, const DataValue &defaultv) const;
		s32 gets32(const str &cPath, const s32 defaultv) const;

	private:
		DataMap m_rootNode;
		DataValue m_invalid;
	};
}

#endif
