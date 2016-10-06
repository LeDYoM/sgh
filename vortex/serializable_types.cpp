#include "include/serializable_types.hpp"

namespace vtx
{
	void DoSerialize(SerializationObject &sobj, const vector2ds32 &v)
	{
		sobj.addValue("x", v.x);
		sobj.addValue("y", v.y);
	}
}


