#ifndef LIB__INPUTRECEIVER_HPP__
#define LIB__INPUTRECEIVER_HPP__

#include <lib/include/types.hpp>
#include <lib/include/key.hpp>

namespace lib
{

	class InputReceiverNode
	{
	public:
		InputReceiverNode() {}
		virtual ~InputReceiverNode() {}
		
		virtual void onKeyPressed(const Key &) {}
		virtual void onKeyReleased(const Key &) {}
	};
}

#endif
