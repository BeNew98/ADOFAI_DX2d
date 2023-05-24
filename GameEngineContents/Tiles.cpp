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
	case TileDeg::Deg0:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_4_Sprite.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		break;
	}
	case TileDeg::Deg90:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_0_Sprite.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		break;
	}
	case TileDeg::Deg270:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_0_Sprite.png");
		m_pRender->GetTransform()->AddLocalRotation({ 0.f, 0.f, 90.f });
		//m_pRender->SetFlipY();
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

