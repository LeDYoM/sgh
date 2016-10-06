#ifndef VTX_SERIALIZATION_OBJECT_INCLUDE_HPP
#define VTX_SERIALIZATION_OBJECT_INCLUDE_HPP

#include "comp_config.hpp"
#include "common_def.hpp"
#include "str.hpp"
#include "types.hpp"
#include "nocopy.hpp"

namespace vtx
{
	class ISerializable;

	enum class SerializationTypes : u32
	{
		Tint = 0,
		Tfloat,
		Tstr,
	};

	enum class SerializationFormat : u32
	{
		VSO, // JSON similar
		VML, // XML similar
		VBF  // Binary
	};

	class VORTEX_API SerializationObject : public NoCopy
	{
	public:
		SerializationObject();
		~SerializationObject();
		void addValue(const Str&, const Str&);
		void addValue(const Str&, const s32);

		template <typename T>
		void addObject(const Str&name, const T&v)
		{
			DoSerialize(*this, v);
		}

		static SerializationFormat serializationFormat() noexcept;
		static void setSerializationFormat(const SerializationFormat) noexcept;
	private:
		friend SerializationObject &&createFromFile(const Str&);
		DECLARE_PRIVATE_MPRIVATE_PIMPL(SerializationObject)
	};

	SerializationObject VORTEX_API &&createFromFile(const Str&);
}

#endif

