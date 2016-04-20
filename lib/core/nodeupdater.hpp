#ifndef LIB_NODEUPDATER_HPP__
#define LIB_NODEUPDATER_HPP__

#include "appservice.hpp"

namespace lib
{
	namespace draw
	{
		class Node;
	}

	class NodeUpdater : public AppService
	{
	public:
		virtual void updateNode(const sptr<draw::Node> &node) = 0;
	};
}
#endif
