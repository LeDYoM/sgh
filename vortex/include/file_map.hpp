#ifndef VTX_FILE_MAP_INCLUDE_HPP
#define VTX_FILE_MAP_INCLUDE_HPP

#include "comp_config.hpp"
#include "str.hpp"
#include "iserializable.hpp"

namespace vtx
{
	class VORTEX_API FileMap
	{
	public:
		FileMap(const Str&);
		~FileMap();

		void addProperty(ISerializable *serializableProperty);
		bool write();
	private:
		DECLARE_PRIVATE_MPRIVATE_PIMPL(FileMap)
	};
}

#endif
