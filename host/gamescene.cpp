#include "gamescene.hpp"

#include "tile.hpp"
#include "player.hpp"
#include "common.hpp"
#include <lib/board/boardmodel.hpp>
#include <lib/board/itilescontroller.hpp>
#include <lib/core/log.hpp>
#include <lib/core/resource.hpp>
#include <lib/core/managers/fontmanager.hpp>
#include <lib/draw/rendernode.hpp>
#include <lib/draw/nodeshape.hpp>
#include <lib/draw/nodetext.hpp>
#include <lib/draw/animations.hpp>
#include <lib/core/resource.hpp>
#include <lib/core/randomizer.hpp>
#include <lib/core/utilprovider.hpp>
#include <lib/core/appcontroller.hpp>
#include <memory>
#include <functional>

using namespace lib;
using namespace lib::draw;

namespace zoper
{
	GameScene::GameScene(PIAppContext piAppContext)
		: Scene(piAppContext, "GameScene")
	{
		_gameData.size.x = 18;
		_gameData.size.y = 12;
		_gameData.centerRect.left = 7;
		_gameData.centerRect.top = 4;
		_gameData.centerRect.width = 4;
		_gameData.centerRect.height = 4;
		_gameData.generateTokenZones();
	}

	GameScene::~GameScene()
	{
	}

	bool GameScene::init()
	{
		if (Scene::init())
		{
			m_keyMapping = lib::uptr<KeyMapping>(new KeyMapping(this));
			m_keyMapping->init();
			_mainBoardrg = this->createNewRenderGroup("mainBoard");
			_gameOverrg = this->createNewRenderGroup("gameOverScreen");
			_scorerg = this->createNewRenderGroup("score");
			_levelrg = this->createNewRenderGroup("level");
			_pauserg = this->createNewRenderGroup("pause");

			_scoreText = _scorerg->createText("scoretxt");
			_scoreDisplay = _scorerg->createText("scoredisplay");
			_currentLevelText = _scorerg->createText("scoretxt");
			_currentLevelDisplay = _scorerg->createText("scoredisplay");
			_levelText = _levelrg->createText("leveltxt");
			_levelDisplay = _levelrg->createText("leveldisplay");
			_goalText = _levelrg->createText("leveltxt");
			_goalDisplay = _levelrg->createText("leveldisplay");
			_pauseText = _pauserg->createText("pausetext");

			_gameText = _gameOverrg->createText("gameovergame");
			_overText = _gameOverrg->createText("gameoverover");

			auto resourceManager = service<lib::core::managers::FontManager>();
			_scoreText->setFont(*(resourceManager->getResource("game_scene.scoreFont")->getAsFont()));
			_scoreDisplay->setFont(*(resourceManager->getResource("game_scene.scoreFont")->getAsFont()));
			_currentLevelText->setFont(*(resourceManager->getResource("game_scene.scoreFont")->getAsFont()));
			_currentLevelDisplay->setFont(*(resourceManager->getResource("game_scene.scoreFont")->getAsFont()));
			_gameText->setFont(*(resourceManager->getResource("game_scene.scoreFont")->getAsFont()));
			_overText->setFont(*(resourceManager->getResource("game_scene.scoreFont")->getAsFont()));
			_levelText->setFont(*(resourceManager->getResource("game_scene.scoreFont")->getAsFont()));
			_levelDisplay->setFont(*(resourceManager->getResource("game_scene.scoreFont")->getAsFont()));
			_goalText->setFont(*(resourceManager->getResource("game_scene.scoreFont")->getAsFont()));
			_goalDisplay->setFont(*(resourceManager->getResource("game_scene.scoreFont")->getAsFont()));
			_pauseText->setFont(*(resourceManager->getResource("game_scene.scoreFont")->getAsFont()));

			_scoreText->setString("Score: ");
			increaseScore(0);
			_gameText->setString("GAME");
			_overText->setString("OVER");
			_pauseText->setString("PAUSE");
			_currentLevelText->setString("Level: ");
			_currentLevelDisplay->setString("0");

			_scoreText->setCharacterSize(90);
			_scoreDisplay->setCharacterSize(90);
			_currentLevelText->setCharacterSize(90);
			_currentLevelDisplay->setCharacterSize(90);
			_gameText->setCharacterSize(360);
			_overText->setCharacterSize(360);
			_levelText->setCharacterSize(90);
			_levelDisplay->setCharacterSize(90);
			_goalText->setCharacterSize(90);
			_goalDisplay->setCharacterSize(90);
			_pauseText->setCharacterSize(180);

			_scoreText->color = lib::draw::Color::Blue();
			_scoreDisplay->color = lib::draw::Color::White();
			_currentLevelText->color = lib::draw::Color::Blue();
			_currentLevelDisplay->color = lib::draw::Color::White();
			_gameText->color = lib::draw::Color::White();
			_overText->color = lib::draw::Color::White();
			_levelText->color = lib::draw::Color::Blue();
			_levelDisplay->color = lib::draw::Color::White();
			_goalText->color = lib::draw::Color::Blue();
			_goalDisplay->color = lib::draw::Color::White();
			_pauseText->color = lib::draw::Color::White();

			_scoreText->scale = { 1.0f, 2.0f };
			_scoreDisplay->scale = { 1.0f, 2.0f };
			_levelText->scale = { 1.0f, 2.0f };
			_levelDisplay->scale = { 1.0f, 2.0f };
			_goalText->scale = { 1.0f, 2.0f };
			_goalDisplay->scale = { 1.0f, 2.0f };

			_scorerg->position = { 50, 50 };
			_scoreDisplay->position->x = _scoreText->getLocalBounds().width;

			_currentLevelDisplay->position->x = _currentLevelText->getLocalBounds().width;

			_levelrg->position = { 1250, 50 };
			_goalText->position->y = 200;

			_currentLevelText->position->y = 200;
			_currentLevelDisplay->position->y = 200;
			
			auto _gameBoundingBox(_gameText->getLocalBounds());
			auto _overBoundingBox(_overText->getLocalBounds());
			vector2df sceneCenter( camera()->view().center() );
			_gameText->position = { sceneCenter.x - (_gameBoundingBox.width / 2.0f), sceneCenter.y - _gameBoundingBox.height };
			_overText->position = { sceneCenter.x - (_overBoundingBox.width / 2.0f), sceneCenter.y };

			_pauseText->setAlignment(lib::draw::Alignment::Center);
			_pauseText->position = { 1000.0f, 1000.0f };
			return true;
		}
		return false;
	}

	bool GameScene::deinit()
	{
		Scene::deinit();
		// Remove instances from all nodes.
		return true;
	}

	void GameScene::onEnterScene()
	{
		lib::DataMap &gConfig{ service<lib::SharedData>()->sharedData() };
		_gameData._gameMode = static_cast<GameData::GameModes>(gConfig[GameModeStr].gets32());
		p_boardModel = lib::sptr<lib::board::BoardModel>(new lib::board::BoardModel(_gameData.size, this));
		tilesCreated();
		addPlayer();

		_score = 0;
		_nextTokenPart = 0;
		setLevel(gConfig[StartLevelStr].gets32());
		_gameOverrg->setVisible(false);
		_mainBoardrg->setVisible(true);
		_pauserg->setVisible(false);

		switch (_gameData._gameMode)
		{
		default:
		case GameData::GameModes::Token:
			_levelText->setString("Tokens: ");
			_goalText->setString("Goal: ");
			break;

		case GameData::GameModes::Time:
			_levelText->setString("Time: ");
			_goalText->setString("Goal: ");
			break;
		}

		_levelDisplay->position->x = _levelText->getLocalBounds().width;
		_goalDisplay->position = lib::vector2df{ _goalText->getLocalBounds().width, 200 };

		setState(Playing);

		gameClock.restart();
	}

	void GameScene::onExitScene()
	{
		_mainBoardrg->clear();
		p_boardModel = nullptr;
		p_player = nullptr;
		_backgroundTilesrg = nullptr;
		_backgroundTiles.clear();
	}

	void GameScene::update()
	{
		if (state() == Playing)
		{
			if (_gameData._gameMode == GameData::GameModes::Time)
				updateLevelData();

			if (gameClock.getElapsedTime().asMilliSeconds() > static_cast<lib::u64>(_levelProperties.millisBetweenTokens()))
			{
				// New token
				generateNextToken();
				gameClock.restart();
			}
		}
		else
		{
			
		}
	}

	bool GameScene::switchPause()
	{
		if (state() == Playing)
		{
			setState(Pause);
			_pauserg->setVisible(true);
			lib::sptr<lib::draw::ColorAnimation> ca = lib::sptr<lib::draw::ColorAnimation>(new lib::draw::ColorAnimation("myColorAnimationId", _pauseText->color));
			ca->setDuration(1000);
			ca->setStartValue(lib::draw::Color(255, 255, 255, 0));
			ca->setEndValue(lib::draw::Color(255, 255, 255, 255));
			_pauseText->addAnimation(ca);
			gameClock.pause();
			return true;
		}
		else if (state() == Pause)
		{
			setState(Playing);
			_pauserg->setVisible(false);
			gameClock.resume();
			return false;
		}
		return false;
	}

	void GameScene::setLevel(const lib::u32 nv)
	{
		_levelProperties.setLevel(nv);
		LOG_DEBUG("Level set: " << _levelProperties.currentLevel());
		LOG_DEBUG("Millis between tokens: " << _levelProperties.millisBetweenTokens());
		LOG_DEBUG("Current base score: " << _levelProperties.baseScore());
		LOG_DEBUG("Seconds to next level: " << _levelProperties.stayTime());
		LOG_DEBUG("Tokens to next level: " << _levelProperties.stayTokens());

		_gameData.levelClock.restart();
		_gameData.consumedTokens = 0;

		// Update background tiles
		for (lib::u32 y = 0; y < _gameData.size.y; ++y)
		{
			for (lib::u32 x = 0; x < _gameData.size.x; ++x)
			{
				_backgroundTiles[y][x]->color = _levelProperties.getBackgroundTileColor(x, y, pointInCenter(lib::vector2du32{ x, y }));
				
			}
		}

		updateGoals();
		updateLevelData();
	}

	void GameScene::updateGoals()
	{
		_currentLevelDisplay->setString(std::to_string(_levelProperties.currentLevel()+1));

		switch (_gameData._gameMode)
		{
		default:
		case GameData::GameModes::Token:
			_goalDisplay->setString(std::to_string(_levelProperties.stayTokens()));
			break;

		case GameData::GameModes::Time:
			_goalDisplay->setString(std::to_string(_levelProperties.stayTime()));
			break;
		}
	}

	void GameScene::updateLevelData()
	{
		switch (_gameData._gameMode)
		{
		default:
		case GameData::GameModes::Token:
			_levelDisplay->setString(std::to_string(_gameData.consumedTokens));
			if (_gameData.consumedTokens >= _levelProperties.stayTokens())
				setLevel(_levelProperties.currentLevel() + 1);
			break;

		case GameData::GameModes::Time:
			_levelDisplay->setString(std::to_string(static_cast<lib::u16>(_gameData.levelClock.getElapsedTime().asSeconds())));
			if (_gameData.levelClock.getElapsedTime().asSeconds() >= _levelProperties.stayTime())
				setLevel(_levelProperties.currentLevel() + 1);
			break;
		}
	}

	void GameData::generateTokenZones()
	{
		// From left to right
		_tokenZones[0].zone.left = 0;
		_tokenZones[0].zone.top = centerRect.top;
		_tokenZones[0].zone.width = centerRect.left - 1;
		_tokenZones[0].zone.height = (centerRect.top + centerRect.height) - 1;
		_tokenZones[0].direction = Direction::DirectionData::Right;

		// From top to bottom
		_tokenZones[1].zone.left = centerRect.left;
		_tokenZones[1].zone.top = 0;
		_tokenZones[1].zone.width = (centerRect.left + centerRect.width) - 1;
		_tokenZones[1].zone.height = centerRect.top - 1;
		_tokenZones[1].direction = Direction::DirectionData::Down;

		// From right to left
		_tokenZones[2].zone.left = size.x - 1;
		_tokenZones[2].zone.top = centerRect.top;
		_tokenZones[2].zone.width = (centerRect.left + centerRect.width);
		_tokenZones[2].zone.height = (centerRect.height + centerRect.height) - 1;
		_tokenZones[2].direction = Direction::DirectionData::Left;

		// From bottom to top
		_tokenZones[3].zone.left = centerRect.left;
		_tokenZones[3].zone.top = size.y - 1;
		_tokenZones[3].zone.width = (centerRect.left + centerRect.width) - 1;
		_tokenZones[3].zone.height = centerRect.top + centerRect.height;
		_tokenZones[3].direction = Direction::DirectionData::Up;

		for (lib::u32 i = 0; i < NUMWAYS; ++i)
		{
			_tokenZones[i].size = _tokenZones[i].direction.isHorizontal() ? centerRect.height : centerRect.width;
		}
	}

	void GameScene::generateNextToken()
	{
		const GameData::TokenZone &currentTokenZone = _gameData._tokenZones[_nextTokenPart];

		LOG_DEBUG("NextTokenPart: " << std::to_string(_nextTokenPart));
		LOG_DEBUG("x1: " << currentTokenZone.zone.left << " y1: " << currentTokenZone.zone.top << 
			" x2: " << currentTokenZone.zone.width << " y2: " << currentTokenZone.zone.height);

		lib::u32 newToken{ utilProvider()->getRandomNumer(NUMTOKENS) };
		lib::u32 sizep{ utilProvider()->getRandomNumer(currentTokenZone.size) };

		lib::u32 newX{ currentTokenZone.zone.left + (currentTokenZone.direction.isHorizontal() ? 0 : sizep) };
		lib::u32 newY{ currentTokenZone.zone.top + (currentTokenZone.direction.isHorizontal() ? sizep : 0) };
		LOG_DEBUG("New tile pos: " << newX << "," << newY);

		lib::vector2du32 loopPosition{ (currentTokenZone.direction.isHorizontal() ? currentTokenZone.zone.width : newX),
			(currentTokenZone.direction.isHorizontal() ? newY : currentTokenZone.zone.height) };
		LOG_DEBUG("Starting at: " << loopPosition.x << "," << loopPosition.y);

		// Now, we have the data for the new token generated, but first, lets start to move the row or col.
		Direction loopDirection = currentTokenZone.direction.negate();
		for_each_token_in_line(loopPosition, loopDirection, [this](const lib::vector2du32 &loopPosition, const Direction &direction)
		{
			if (!p_boardModel->tileEmpty(loopPosition))
			{
				lib::vector2du32 dest = direction.negate().applyToVector(loopPosition);
				p_boardModel->moveTile(loopPosition, dest);

				if (pointInCenter(dest))
				{
					startGameOver();
				}
			}
			return true;
		});
		// Set the new token
		addNewToken(lib::vector2du32{ newX, newY }, newToken);
		_nextTokenPart = (_nextTokenPart + 1) % NUMWAYS;

		EXECUTE_IN_DEBUG(_debugDisplayBoard());
	}

	void GameScene::startGameOver()
	{
		setState(GameOver);
		_gameOverrg->setVisible(true);
	}

	void GameScene::for_each_token_in_line(const lib::vector2du32 &startPosition, const Direction &direction,
		std::function<bool(const lib::vector2du32 &, const Direction &)> updatePredicate)
	{
		lib::vector2du32 loopPosition{ startPosition };
		// Now, we have the data for the new token generated, but first, lets start to move the row or col.
		bool stay{ true };
		do
		{
			stay &= updatePredicate(loopPosition, direction);
			loopPosition = direction.applyToVector(loopPosition);
			stay &= p_boardModel->validCoords(loopPosition);
		} while (stay);
	}

	void GameScene::addPlayer()
	{
		LOG_DEBUG("Adding player tile at " << _gameData.centerRect.top << "," << _gameData.centerRect.height);
		__ASSERT(!p_player, "Player already initialized");
		// Create the player instance
		p_player = lib::sptr<Player>(new Player(this, lib::vector2du32(_gameData.centerRect.leftTop()),tileSize()));

		// Add it to the board and to the scene nodes
		p_boardModel->setTile(p_player->boardPosition(), std::dynamic_pointer_cast<lib::board::ITile>(_mainBoardrg->addNode(p_player)));
	}

	void GameScene::addNewToken(const lib::vector2du32 &_position, lib::u32 newToken)
	{
		LOG_DEBUG("Adding new tile at " << _position.x << "," << _position.y << " with value " << newToken);
		// Create a new Tile instance
		lib::sptr<Tile> newTileToken = lib::sptr<Tile>(new Tile(this, lib::board::BoardTileData(newToken),tileSize()));
		// Set the position in the scene depending on the board position
		newTileToken->position = board2Scene(_position);

		// Add it to the board and to the scene nodes
		p_boardModel->setTile(_position, std::dynamic_pointer_cast<lib::board::ITile>(_mainBoardrg->addNode(newTileToken)));
	}

	void GameScene::onKeyPressed(const lib::Key &key)
	{
		Scene::onKeyPressed(key);
		switch (state())
		{
		case Playing:
		{
			auto dir = m_keyMapping->getDirectionFromKey(key.kCode);
			if (dir.isValid())
			{
				p_player->setCurrentDirection(dir);
				movePlayer(dir);
			}
			else if (m_keyMapping->isLaunchKey(key.kCode))
			{
				launchPlayer();
			}
			else if (m_keyMapping->isPauseKey(key.kCode))
			{
				switchPause();
			}
		}
		break;
		case GameOver:
			setNextScene("MenuScene");
			break;
		case Pause:
			if (m_keyMapping->isPauseKey(key.kCode))
			{
				switchPause();
			}
			break;
		}
	}

	void GameScene::movePlayer(const Direction & dir)
	{
		__ASSERT(dir.isValid(), "Invalid direction passed to move");
		auto nPosition = dir.applyToVector(p_player->boardPosition());
		if (pointInCenter(nPosition))
		{
			p_boardModel->moveTile(p_player->boardPosition(), lib::vector2du32(nPosition.x,nPosition.y));
			p_player->setBoardPosition(lib::vector2du32(nPosition.x, nPosition.y));
		}
		else
		{
			updatePlayer(p_player->boardPosition(), p_player);
		}
	}

	void GameScene::onKeyReleased(const lib::Key &key)
	{
		key;
	}

	void GameScene::onAnimationStarted(lib::sptr<lib::draw::anim::IAnimation> anim, lib::sptr<lib::draw::RenderNode> node)
	{
	}

	void GameScene::onAnimationFinished(lib::sptr<lib::draw::anim::IAnimation> anim, lib::sptr<lib::draw::RenderNode> node)
	{
		/*
		if (anim->animationType() == "ColorAnimation" && node == _pauseText)
		{
			_pauserg->setVisible(state()==Pause);
			_pauseText->setColor(lib::draw::Color::White());
		}
		else if (anim->animationType() == "PositionAnimation" && node->name() == "pointIncrementScore")
		{
			removeNode(node);
		}
		*/
	}

	void GameScene::launchPlayer()
	{
		LOG_DEBUG("Launching player");
		const Direction loopDirection = p_player->currentDirection();
		lib::vector2du32 loopPosition{ p_player->boardPosition() };
		lib::board::BoardTileData tokenType = p_player->getData();
		lib::u32 inARow{ 0 };
		for_each_token_in_line(loopPosition, loopDirection, [this,tokenType,&inARow](const lib::vector2du32 &loopPosition, const Direction &direction)
		{
			direction;
			bool result{ true };
			bool found{ false };
			lib::vector2df lastTokenPosition;

			if (!p_boardModel->tileEmpty(loopPosition) && !pointInCenter(loopPosition) && result)
			{
				lib::sptr<lib::board::ITile> currentToken{ p_boardModel->getTile(loopPosition).lock() };
				lib::board::BoardTileData currentTokenType = currentToken->getData();
				if (currentTokenType == tokenType)
				{
					++inARow;
					increaseScore(inARow*_levelProperties.baseScore());
					_gameData.consumedTokens++;
					lastTokenPosition = board2Scene(loopPosition);
					p_boardModel->deleteTile(loopPosition);
					found = true;
				}
				else
				{
					p_boardModel->changeTileData(p_player->boardPosition(), currentTokenType);
					p_boardModel->changeTileData(loopPosition, tokenType);
					LOG_DEBUG("Player type changed to " << p_player->getData());
					result = false;
				}
			}
			if (found)
			{
				auto node = createShape("pointIncrementScore", lib::vector2df{ 15.0f,15.0f });
				/*
				lib::sptr<lib::draw::PositionAnimation> pa = lib::sptr<lib::draw::PositionAnimation>(new lib::draw::PositionAnimation("myPositionAnimationId"));
				pa->setDuration(600);
				pa->setStartValue(lastTokenPosition);
				pa->setEndValue(lib::vector2df(450, 100));
				node->addAnimation(pa);
				*/
			}
			return result;
		});

		if (_gameData._gameMode == GameData::GameModes::Token)
			updateLevelData();
	}

	bool GameScene::pointInCenter(const lib::vector2du32 &_position) const
	{
		if (p_boardModel->validCoords(_position))
		{
			if (_position.x < _gameData.centerRect.left || _position.y < _gameData.centerRect.top)
				return false;

			if (_position.x >= _gameData.centerRect.right() || _position.y >= _gameData.centerRect.bottom())
				return false;

			return true;
		}
		return false;
	}

	const lib::vector2df GameScene::board2Scene(const lib::vector2du32 &bPosition) const
	{
		return pointViewToCurrentView(lib::vector2df{ static_cast<lib::f32>(bPosition.x), static_cast<lib::f32>(bPosition.y) },
			lib::vector2df{ static_cast<lib::f32>(p_boardModel->size().x), static_cast<lib::f32>(p_boardModel->size().y) });
	}

	const lib::vector2df GameScene::tileSize() const
	{
		return board2Scene(lib::vector2du32{ 1, 1 });
	}

	void GameScene::_debugDisplayBoard() const
	{
		for (lib::u32 y = 0; y < _gameData.size.y; ++y)
		{
			std::string temp;
			for (lib::u32 x = 0; x < _gameData.size.x; ++x)
			{
				std::string chTemp;
				auto lp_tile = p_boardModel->getTile(lib::vector2du32{ x, y }).lock();
				if (lp_tile)
				{
					chTemp = std::to_string(lp_tile->getData());
				}
				else
				{
					chTemp = "*";
					if (pointInCenter(lib::vector2du32(x, y)))
						chTemp = "C";
				}

				temp += chTemp;
			}
			LOG_DEBUG(temp);
		}
	}

	void GameScene::tilesCreated()
	{
		_backgroundTilesrg = createNewRenderGroup("backgroundTiles", _mainBoardrg);
		for (lib::u32 y = 0; y < _gameData.size.y; ++y)
		{
			std::vector<lib::sptr<lib::draw::NodeShape>> column;

			for (lib::u32 x = 0; x < _gameData.size.x; ++x)
			{
				auto tileBackground = _backgroundTilesrg->createSpriteShape("backgroundTile", tileSize());
				tileBackground->position = board2Scene(lib::vector2du32{ x,y });
				column.push_back(tileBackground);

				auto node = _backgroundTilesrg->createShape("backgroundTilePoint", lib::vector2df{ 10.0f,10.0f });
				lib::vector2df center( board2Scene(lib::vector2du32{ x,y }) );
				center.x += tileSize().x / 2.0f;
				center.y += tileSize().y / 2.0f;
				center.x -= (node->getLocalBounds().width / 2.0f);
				center.y -= (node->getLocalBounds().height / 2.0f);
				node->position = center;
				node->color = lib::draw::Color::White();
			}
			_backgroundTiles.push_back(column);
		}
	}

	void GameScene::tileAdded(const lib::vector2du32 &_position, lib::board::WITilePointer nTile)
	{
		// Tile appeared
		if (auto ztile = std::dynamic_pointer_cast<Tile>(nTile.lock()))
		{
			tokenAppeared(_position, ztile);
		}
		else if (auto ztile_ = std::dynamic_pointer_cast<Player>(nTile.lock()))
		{
			// Set the position in the scene depending on the board position
			playerAppeared(_position, ztile_);
		}
	}

	void GameScene::tileDeleted(const lib::vector2du32 &_position, lib::board::WITilePointer nTile)
	{
		if (auto ztile = std::dynamic_pointer_cast<Tile>(nTile.lock()))
		{
			tokenDissapeared(_position,ztile);
		}
		else if (auto ztile_ = std::dynamic_pointer_cast<Player>(nTile.lock()))
		{
			playerDissapeared(_position,ztile_);
		}
	}

	void GameScene::tileMoved(const lib::vector2du32 &source, const lib::vector2du32 &dest, lib::board::WITilePointer tile)
	{
		if (auto ztile = as<Tile>(tile.lock()))
		{
			tokenMoved(source, dest, ztile);
		}
		else if (auto ztile_ = as<Player>(tile.lock()))
		{
			playerMoved(source, dest, ztile_);
		}
	}

	void GameScene::tileChanged(const lib::vector2du32 &_position, lib::board::WITilePointer nTile, 
		const lib::board::BoardTileData &ov, const lib::board::BoardTileData &nv)
	{
		if (auto ztile = std::dynamic_pointer_cast<Tile>(nTile.lock()))
		{
			tokenChangedValue(_position, ztile, ov, nv);
		}
		else if (auto ztile_ = std::dynamic_pointer_cast<Player>(nTile.lock()))
		{
			playerChangedValue(_position, ztile_, ov, nv);
		}
	}

	void GameScene::tokenMoved(const lib::vector2du32 &source, const lib::vector2du32 &dest, lib::sptr<Tile> tile)
	{
		source;
		dest;
		/*
		lib::sptr<lib::draw::PositionAnimation> pa = lib::sptr<lib::draw::PositionAnimation>(new lib::draw::PositionAnimation("myPositionAnimationId"));
		pa->setDuration(_levelProperties.millisBetweenTokens() / 2);
		pa->setStartValue(tile->position());
		pa->setEndValue(board2Scene(dest));
		tile->addAnimation(pa);
		*/
	}

	void GameScene::tokenAppeared(const lib::vector2du32 &_position, lib::sptr<Tile> tile)
	{
		_position;
		tile;
	}

	void GameScene::tokenDissapeared(const lib::vector2du32 &_position, lib::sptr<Tile> tile)
	{
		_position;
		LOG_DEBUG("Deleting token " << tile->name() << " from scene");
		_mainBoardrg->removeNode(tile);
	}

	void GameScene::tokenChangedValue(const lib::vector2du32 &_position, lib::sptr<Tile> tile,
		const lib::board::BoardTileData &ov, const lib::board::BoardTileData &nv)
	{
		_position; nv; ov;
		tile->color = tile->getColorForToken();
	}

	void GameScene::updatePlayer(const lib::vector2du32 &dest, lib::sptr<Player> player_)
	{
//		player_->origin = (tileSize() / 2.0f);
		player_->position = (board2Scene(dest) + (tileSize() / 2.0f));
		player_->rotation = player_->currentDirection().angle();
	}

	void GameScene::playerMoved(const lib::vector2du32 &source, const lib::vector2du32 &dest, lib::sptr<Player> player_)
	{
		source;
		updatePlayer(dest, player_);
	}

	void GameScene::playerAppeared(const lib::vector2du32 &_position, lib::sptr<Player> player)
	{
		player->position = board2Scene(_position);
	}

	void GameScene::playerDissapeared(const lib::vector2du32 &_position, lib::sptr<Player> player)
	{
		_position;
	}

	void GameScene::playerChangedValue(const lib::vector2du32 &_position, lib::sptr<Player> player,
		const lib::board::BoardTileData &ov, const lib::board::BoardTileData &nv)
	{
		_position; nv; ov;
		player->color = player->getColorForToken();
	}

	void GameScene::increaseScore(lib::u32 scoreIncrement)
	{
		_score += scoreIncrement;
		std::string result{ std::to_string(_score) };
		while (result.size() < _scoreSize) result = "0" + result;
		_scoreDisplay->setString(result);
	}

	const lib::vector2df GameScene::getDefaultSizeView()
	{
		return{ 2000.0f, 2000.0f };
	}
}
