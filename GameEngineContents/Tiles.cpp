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
		m_pRender->SetScaleToTexture("tiles_new_world1_b_0_Sprite.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		m_fStartPivot = { 3.f,27.f};
		m_fEndPivot = { 152.f,27.f };
		break;
	}
	case TileDeg::Deg45:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_45_Sprite.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		m_fStartPivot = { 3.f,58.f };
		m_fEndPivot = { 101.f,18.f };
		break;
	}
	case TileDeg::Deg60:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_60_Sprite.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		m_fStartPivot = m_pRender->GetTransform()->GetLocalScale() - float4{ 3.f,58.f };
		m_fEndPivot = m_pRender->GetTransform()->GetLocalScale() - float4{ 80.f,14.f };
		break;
	}
	case TileDeg::Deg90:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_90_Sprite.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		m_fStartPivot = m_pRender->GetTransform()->GetLocalScale() - float4{ 3.f,37.f };
		m_fEndPivot = m_pRender->GetTransform()->GetLocalScale() - float4{ 37.f,3.f };
		break;
	}
	case TileDeg::Deg120:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_120_Sprite.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		m_fStartPivot = m_pRender->GetTransform()->GetLocalScale() - float4{ 3.f,60.f };
		m_fEndPivot = m_pRender->GetTransform()->GetLocalScale() - float4{ 5.f,55.f };
		break;
	}
	case TileDeg::Deg135:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_135_Sprite.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		m_fStartPivot = m_pRender->GetTransform()->GetLocalScale() - float4{ 9.f,60.f };
		m_fEndPivot = m_pRender->GetTransform()->GetLocalScale() - float4{ 2.f,75.f };
		break;
	}
	case TileDeg::Deg225:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_135_Sprite.png");
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
		m_pRender->SetScaleToTexture("tiles_new_world1_b_90_Sprite.png");
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
		m_pRender->SetScaleToTexture("tiles_new_world1_b_45_Sprite.png");
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

