#ifndef LIB_DRAW_INODETREE_HPP
#define LIB_DRAW_INODETREE_HPP

#include <lib/core/vecsptr.hpp>

namespace lib
{
	template <class T>
	class INodeTree
	{
	protected:
		void addNode(sptr<T> node)
		{
			m_nodes.push_back(node);
			node->init();
		}
		VecSPtr<T> m_nodes;
	private:
	};
}

#endif
