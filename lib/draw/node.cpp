#include "node.hpp"
#include "rendergroup.hpp"

namespace lib
{
	namespace draw
	{
		Node::Node(const str &name) : HasName(name), IDrawable{}, Object{} {}
		
		bool Node::init()
		{
			setProvider(parent());
			return true;
		}
		
		Node::~Node()
		{
		}
		
		void Node::autoUpdate()
		{
			
		}

	}
}
