#include "gamebasetile.hpp"
#include <lib/core/log.hpp>
#define _USE_MATH_DEFINES
#include <math.h>

namespace zoper
{
	GameBaseTile::GameBaseTile(lib::board::BoardTileData data, const sf::Vector2f &size, const std::string &baseName) 
		: lib::board::ITile{ data }, lib::scn::draw::NodeShape(baseName,size,30)
	{
	}

	GameBaseTile::~GameBaseTile()
	{
	}

	lib::scn::draw::Color GameBaseTile::getColorForToken() const
	{

		lib::scn::draw::Color c;

		switch (getData())
		{
		case 0:
			c = lib::scn::draw::Color::Red;
			break;
		case 1:
			c = lib::scn::draw::Color::Green;
			break;
		case 2:
			c = lib::scn::draw::Color::Blue;
			break;
		case 3:
			c = lib::scn::draw::Color::Yellow;
			break;
		case 4:
			c = lib::scn::draw::Color::Magenta;
			break;
		default:
			c = lib::scn::draw::Color::White;
			LOG_ERROR("Error value for token: " << getData() << " is not supported");
			break;
		}
		return c;
	}

}
