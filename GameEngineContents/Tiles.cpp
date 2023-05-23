#include "PrecompileHeader.h"
#include "Tiles.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

Tiles::Tiles() 
{
}

Tiles::~Tiles() 
{
}


void Tiles::CreateTile(TileDeg _TileDeg)
{
	switch (_TileDeg)
	{
	case TileDeg::Start:
	{

		std::shared_ptr<GameEngineSpriteRenderer> m_Start = CreateComponent<GameEngineSpriteRenderer>();
		m_Start->SetScaleToTexture("tiles_editor_basic_12_Sprite.png");
		m_Start->SetFlipX();
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		break;
	}
	case TileDeg::Deg90:
	{
		std::shared_ptr<GameEngineSpriteRenderer>m_90 = CreateComponent<GameEngineSpriteRenderer>();
		m_90->SetScaleToTexture("tiles_editor_basic_0_Sprite.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		break;
	}
	case TileDeg::Deg180:
	{
		std::shared_ptr<GameEngineSpriteRenderer>m_180 = CreateComponent<GameEngineSpriteRenderer>();
		m_180->SetScaleToTexture("tiles_editor_basic_4_Sprite.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		break;
	}
	case TileDeg::Deg270:
	{
		std::shared_ptr<GameEngineSpriteRenderer>m_270 = CreateComponent<GameEngineSpriteRenderer>();
		m_270->SetScaleToTexture("tiles_editor_basic_0_Sprite.png");
		m_270->SetFlipY();
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		break;
	}
	case TileDeg::End:
	{
		std::shared_ptr<GameEngineSpriteRenderer> m_End = CreateComponent<GameEngineSpriteRenderer>();
		m_End->SetScaleToTexture("tiles_editor_basic_12_Sprite.png");
		m_End->SetFlipX();
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		break;
	}
	default:
		break;
	}
}

void Tiles::Start()
{
}

