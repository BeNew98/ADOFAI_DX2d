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

void Tiles::Start()
{
	m_pStartPivot = CreateComponent<GameEngineSpriteRenderer>();
	m_pStartPivot->GetTransform()->SetLocalScale(float4(10.f, 10.f));
	m_pEndPivot = CreateComponent<GameEngineSpriteRenderer>();
	m_pEndPivot->GetTransform()->SetLocalScale(float4(20.f, 20.f));
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
		m_fStartCal = { 3.f,27.f};
		m_fEndCal = { 152.f,27.f };
		break;
	}
	case TileDeg::Deg45:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_45_Sprite.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		m_fStartCal = { 3.f,58.f };
		m_fEndCal = { 101.f,18.f };
		break;
	}
	case TileDeg::Deg60:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_60_Sprite.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		m_fStartCal =float4{ 3.f,58.f };
		m_fEndCal =float4{ 80.f,14.f };
		break;
	}
	case TileDeg::Deg90:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_90_Sprite.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		m_fStartCal =float4{ 3.f,37.f };
		m_fEndCal = float4{ 37.f,3.f };
		break;
	}
	case TileDeg::Deg120:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_120_Sprite.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		m_fStartCal = float4{ 3.f,60.f };
		m_fEndCal = float4{ 5.f,55.f };
		break;
	}
	case TileDeg::Deg135:
	{
		m_pRender = CreateComponent<GameEngineSpriteRenderer>();
		m_pRender->SetScaleToTexture("tiles_new_world1_b_135_Sprite.png");
		std::shared_ptr<GameEngineCollision> Collision = CreateComponent<GameEngineCollision>(OrderNum::MAP);
		m_fStartCal = float4{ 9.f,60.f };
		m_fEndCal = float4{ 2.f,75.f };
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
	m_fStartBetPos = GetTransform()->GetLocalPosition() - m_pRender->GetTransform()->GetLocalScale().half() + m_fStartCal;
	m_fStartBetPos.y = -m_fStartBetPos.y;
	m_pStartPivot->GetTransform()->SetLocalPosition(m_fStartBetPos);

	m_fEndBetPos = m_fEndCal- m_fStartCal;
	m_fEndBetPos.y = -m_fEndBetPos.y;
}


void Tiles::CalPosition(int _Deg)
{
	
	float4 StartPivotPos = m_pStartPivot->GetTransform()->GetLocalPosition();
	GetTransform()->SetLocalPosition(StartPivotPos);
	//m_fStartBetPos.RotaitonZDeg(static_cast<float>(_Deg));
	GetTransform()->AddLocalPosition(m_fStartBetPos);

	m_pEndPivot->GetTransform()->SetLocalPosition(StartPivotPos);
	m_fEndBetPos.RotaitonZDeg(static_cast<float>(_Deg));
	m_pEndPivot->GetTransform()->AddLocalPosition(m_fEndBetPos);
	//m_pStartPivot->Death();
}

void Tiles::SetStartPivotPos(float4 _EndPivotPos )
{
	m_pStartPivot->GetTransform()->SetWorldPosition(_EndPivotPos);
}
