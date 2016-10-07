#ifndef VTX_FILEMAPPED_INCLUDE_HPP
#define VTX_FILEMAPPED_INCLUDE_HPP

#include "comp_config.hpp"
#include "common_def.hpp"
#include "str.hpp"
#include "serialization_object.hpp"
#include "singleton.hpp"

namespace vtx
{
	class VORTEX_API FileMapped : public Singleton<FileMapped>
	{
	public:
		FileMapped();
		~FileMapped();
		void startSave();
		void endSave();
		virtual inline void save() {}
	protected:
		inline void setFileName(const Str &fileName) noexcept { m_fileName = fileName; }
		SerializationObject *so() const noexcept { return m_serializationObject; }
	private:
		SerializationObject *m_serializationObject;
		Str m_fileName;
	};
}

#endif

