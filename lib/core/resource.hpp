#ifndef __RESOURCE_HPP__
#define __RESOURCE_HPP__

#include <lib/include/types.hpp>
#include "log.hpp"

namespace sf
{
	class Font;
	class Texture;
}

namespace lib
{
	class Resource
	{
	public:
		enum class ResourceType
		{
			Empty = 0,
			Font = 1,
			Texture = 2,
			MaxResourceType = 0xffff
		} _resourceType{ ResourceType::Empty };

		Resource(const Resource &) = delete;
		Resource(ResourceType rType, const std::string &file, const std::string &id);
		virtual ~Resource();

		inline bool isValid() const { return _isValid; }
		sf::Font *getAsFont() const { __ASSERT(_resourceType == ResourceType::Font, "Resource is not a font"); return _resourceData.font; }
		sf::Texture *getAsTexture() const { __ASSERT(_resourceType == ResourceType::Texture ,"Resource is not a font"); return _resourceData.texture; }

		inline const str &id() const { return m_id; }
	private:
		bool _isValid{ false };
		str m_id;
		union ResourceData
		{
			sf::Font *font{ nullptr };
			sf::Texture *texture;
		} _resourceData;
	};
}

#endif
