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
		static void initialize();
		bool updateFile();
	protected:
		FileMapped();
		~FileMapped();

		void startSave();
		void endSave();
		virtual inline void save() {}

		inline void setFileName(const Str &fileName) noexcept { m_fileName = fileName; }
		SerializationObject *so() const noexcept { return m_serializationObject; }
	private:
		friend class Singleton<FileMapped>;
		SerializationObject *m_serializationObject;
		Str m_fileName;
	};
}

#endif

