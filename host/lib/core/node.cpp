#include "node.hpp"

namespace lib
{
	namespace core
	{
		Node::Node(const std::string &name, Node *parent)
			: m_name( name ), m_parent{ parent }, 
			m_transformable{ uptr<draw::Transformable>(new draw::Transformable{}) }
		{
		}

		Node::~Node()
		{
		}

		void Node::sendEvent(uptr<events::Event> e)
		{
			m_pendingEvents.push_back(std::move(e));
		}

	}
}