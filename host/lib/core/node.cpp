#include "node.hpp"

namespace lib
{
	namespace core
	{
		Node::Node(const std::string &name, Node *parent)
			: m_name{ name }, m_parent{ parent }
		{
		}

		Node::~Node()
		{
		}
	}
}