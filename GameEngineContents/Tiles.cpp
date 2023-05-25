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
		m_pRender->SetScaleToTexture("tiles_new_world1_b_4_Sprite_Test.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		break;
	}
	case TileDeg::Deg90:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_0_Sprite_Test.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		break;
	}
	case TileDeg::Deg270:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_0_Sprite_Test.png");
		//m_pRender->GetTransform()->AddLocalRotation({ 0.f, 0.f, 90.f });
		m_pRender->SetFlipY();
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		break;
	}
	default:
		break;
	}
	switch (_TileDeg)
	{
	case TileDeg::Deg0:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_4_Sprite_Test.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		break;
	}
	case TileDeg::Deg45:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_45_Sprite_Test.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		break;
	}
	case TileDeg::Deg60:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_60_Sprite.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		break;
	}
	case TileDeg::Deg90:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_0_Sprite_Test.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		break;
	}
	case TileDeg::Deg120:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_120_Sprite.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		break;
	}
	case TileDeg::Deg135:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_140_Sprite.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		break;
	}
	case TileDeg::Deg225:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_140_Sprite.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		m_pRender->SetFlipY();
		break;
	}
	case TileDeg::Deg240:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_120_Sprite.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		m_pRender->SetFlipY();
		break;
	}
	case TileDeg::Deg270:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_0_Sprite_Test.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		m_pRender->SetFlipY();
		break;
	}
	case TileDeg::Deg300:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_60_Sprite.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		m_pRender->SetFlipY();
		break;
	}
	case TileDeg::Deg315:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_45_Sprite_Test.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		m_pRender->SetFlipY();
		break;
	}
	default:
		break;
	}
}

void Tiles::Start()
{
}

