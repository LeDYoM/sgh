#ifndef LIB__INPUTRECEIVER_HPP__
#define LIB__INPUTRECEIVER_HPP__

#include <lib/include/types.hpp>
#include <lib/include/key.hpp>
#include "../draw/node.hpp"

namespace lib
{

	class InputReceiverNode : public virtual draw::Node
	{
	public:
		InputReceiverNode(const str&str_) :draw::Node{ str_ } {}
		virtual ~InputReceiverNode() {}
		
		virtual void onKeyPressed(const Key &) {}
		virtual void onKeyReleased(const Key &) {}
	};
}

#endif
