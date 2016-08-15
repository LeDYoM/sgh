#ifndef __LIB_RESOURCELOADCONTROLLER_HPP__
#define __LIB_RESOURCELOADCONTROLLER_HPP__

#include <lib/include/types.hpp>
#include "strmap.hpp"

namespace lib
{
	namespace core
	{
		namespace managers
		{
			class FileManager;
			class FontManager;
			class TextureManager;
		}
		class ResourceLoadController
		{
		public:
			ResourceLoadController(const StringMap &, const str &, managers::FileManager *const,
				managers::FontManager *const, managers::TextureManager *const);
			virtual ~ResourceLoadController();

			bool operator()();
		private:
			StringMap m_stringMap;
			const str m_section;
			managers::FileManager *const m_fileManager;
			managers::FontManager *const m_fontManager;
			managers::TextureManager *const m_textureManager;
		};
	}
}

#endif
