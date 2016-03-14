#ifndef LIB_NODE_HPP
#define LIB_NODE_HPP

#include <string>
#include <vector>
#include <lib/draw/transformable.hpp>
#include <lib/core/events/event.hpp>

namespace lib
{
	namespace core
	{
		class Node
		{
		public:
			explicit Node(const std::string &name, Node *parent=nullptr);
			virtual ~Node();

			void sendEvent(uptr<events::Event> e);
		private:
			std::string m_name;
			std::vector<Node> m_nodes;
			Node *const m_parent;
			uptr<draw::Transformable> m_transformable;
			std::vector<sptr<events::Event>> m_pendingEvents;
		};
	}
}
#endif
