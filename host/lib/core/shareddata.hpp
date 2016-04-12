#ifndef LIB_SHAREDDATA_HPP__
#define LIB_SHAREDDATA_HPP__

#include <lib/include/types.hpp>
#include "appservice.hpp"
#include "data.hpp"


namespace lib
{
	class SharedData : public AppService
	{
	public:
		SharedData();
		virtual ~SharedData();
		static const str staticTypeName() { return "SharedData"; }

		DataMap &sharedData();
		void Init() override;

	private:
		DataMap m_rootNode;
	};
}

#endif
