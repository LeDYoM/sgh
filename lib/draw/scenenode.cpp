#include "scenenode.hpp"
#include "rendergroup.hpp"

namespace lib
{
	namespace draw
	{
		SceneNode::SceneNode(const str &name) : m_name( name ) {}
		
		bool SceneNode::init()
		{
			setProvider(parent());
			return true;
		}
		
		SceneNode::~SceneNode()
		{
		}
	
	}
}
