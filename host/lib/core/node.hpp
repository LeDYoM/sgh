#ifndef LIB_NODE_HPP
#define LIB_NODE_HPP

#include <string>
#include <vector>

namespace lib
{
	namespace core
	{
		class Node
		{
		public:
			explicit Node(const std::string &name, Node *parent=nullptr);
			virtual ~Node();

		private:
			std::string m_name;
			std::vector<Node> m_nodes;
			Node *const m_parent;
		};
	}
}
#endif
