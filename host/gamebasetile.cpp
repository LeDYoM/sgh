#include "gamebasetile.hpp"
#include <lib/core/log.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

namespace zoper
{
	GameBaseTile::GameBaseTile(lib::board::BoardTileData data, const lib::vector2df &size, const std::string &baseName) 
		: lib::board::ITile{ data }, lib::draw::NodeShape(baseName,size,30)
	{
	}

	GameBaseTile::~GameBaseTile()
	{
	}

	lib::draw::Color GameBaseTile::getColorForToken() const
	{
		switch (getData())
		{
		case 0:
			return lib::draw::Color::Red();
			break;
		case 1:
			return lib::draw::Color::Green();
			break;
		case 2:
			return lib::draw::Color::Blue();
			break;
		case 3:
			return lib::draw::Color::Yellow();
			break;
		case 4:
			return lib::draw::Color::Magenta();
			break;
		default:
			LOG_ERROR("Error value for token: " << getData() << " is not supported");
			return lib::draw::Color::White();
			break;
		}
	}

}
