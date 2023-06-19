#include "PrecompileHeader.h"
#include "Tiles.h"
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "SquareGlowEffect.h"
#include "RoundGlowEffect.h"

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

	m_pCenterPivot = CreateComponent<GameEngineComponent>();
}

void Tiles::Update(float _DeltaTime)
{
	EventStart(_DeltaTime);
	if (m_fData.iz()!=360&& true == m_bGlow)
	{
		if (nullptr == m_pRGlow)
		{
	
			m_pRGlow = GetLevel()->CreateActor<RoundGlowEffect>(OrderNum::EFFECT);
			m_pRGlow->GetTransform()->SetLocalPosition(m_pCenterPivot->GetTransform()->GetWorldPosition());
		}
	}
	else if (m_fData.iz() == 360 && true == m_bGlow)
	{
		if (nullptr == m_pSGlow)
		{
			m_pSGlow = GetLevel()->CreateActor<SquareGlowEffect>(OrderNum::EFFECT);
			m_pSGlow->GetTransform()->SetLocalPosition(m_pCenterPivot->GetTransform()->GetWorldPosition());
			m_pSGlow->SetIndex(m_iIndex);
		}
	}

	if (m_bAlpha == true)
	{
		if (m_fAlpha <= 0.f)
		{
			return;
		}
		m_fAlpha -= _DeltaTime / 0.3f;
		m_pRender->ColorOptionValue.MulColor ={ 1.f,1.f,1.f,m_fAlpha };
		if (m_pSGlow == nullptr)
		{
			return;
		}
		m_pSGlow->GetRender()->ColorOptionValue.MulColor = { 1.f,1.f,1.f,m_fAlpha };
	}
	else
	{
		if (m_fAlpha >= 1.f)
		{
			return;
		}
		m_fAlpha += _DeltaTime / 0.3f;
		m_pRender->ColorOptionValue.MulColor = { 1.f,1.f,1.f,m_fAlpha };
		if (m_pSGlow==nullptr)
		{
			return;
		}
		m_pSGlow->GetRender()->ColorOptionValue.MulColor = { 1.f,1.f,1.f,m_fAlpha };
	}
}

void Tiles::EventStart(float _DeltaTime)
{
	if (m_bEventTrigger == false)
	{
		return;
	}
	ZoomEvent(_DeltaTime);
}

void Tiles::ZoomEvent(float _DeltaTime)
{
	std::map<EventType, std::vector<TileEvent>>::iterator findIter = m_mapAllEvent.find(EventType::ZOOM);

	std::vector<TileEvent> *vecEvt = &findIter->second;

	for (size_t i = 0; i < (*vecEvt).size(); i++)
	{
		if (true == (*vecEvt)[i].End)
		{
			continue;
		}
		TileEvent Evt = (*vecEvt)[i];
		{

			float fRatio = GetLevel()->GetMainCamera()->GetZoomRatio();
			if (Evt.Ratio > 0.f)
			{
				if ((m_PrevRatio - Evt.Ratio) >= fRatio)
				{
					GetLevel()->GetMainCamera()->SetZoomRatio(m_PrevRatio - Evt.Ratio);
					m_PrevRatio = GetLevel()->GetMainCamera()->GetZoomRatio();
					(*vecEvt)[i].End = true;
					return;
				}
			}
			else
			{
				if ((m_PrevRatio - Evt.Ratio) <= fRatio)
				{
					GetLevel()->GetMainCamera()->SetZoomRatio(m_PrevRatio - Evt.Ratio);
					m_PrevRatio = GetLevel()->GetMainCamera()->GetZoomRatio();
					(*vecEvt)[i].End = true;
					return;
				}
			}

			float ZoomRatio = Evt.Ratio * _DeltaTime / Evt.Time;
			GetLevel()->GetMainCamera()->AddZoomRatio(ZoomRatio);
			return;
		}
	}
}


void Tiles::CreateTile(TileDeg _TileDeg)
{
	m_pRender = CreateComponent<GameEngineSpriteRenderer>(OrderNum::MAP);
	switch (_TileDeg)
	{
	case TileDeg::Deg0:
	{
		m_pRender->SetScaleToTexture("tiles_new_world1_b_0_Sprite.png");
		m_fStartCal ={ 3.f,28.f};
		m_fEndCal = { 153.f,28.f };
		m_pCenterPivot->GetTransform()->AddLocalPosition({ 0.f,16.f });
		break;
	}
	case TileDeg::Deg45:
	{
		m_pRender->SetScaleToTexture("tiles_new_world1_b_45_Sprite.png");
		m_fStartCal = { 3.f,59.f }	;
		m_fEndCal	= { 102.5f,17.5f };
		break;
	}
	case TileDeg::Deg60:
	{
		m_pRender->SetScaleToTexture("tiles_new_world1_b_60_Sprite.png");
		m_fStartCal =float4{ 3.f,58.f };
		m_fEndCal =float4{ 80.f,14.f };
		break;
	}
	case TileDeg::Deg90:
	{
		m_pRender->SetScaleToTexture("tiles_new_world1_b_90_Sprite.png");
		m_fStartCal =float4{ 3.f,37.f };
		m_fEndCal = float4{ 38.f,2.f };
		break;
	}
	case TileDeg::Deg120:
	{
		m_pRender->SetScaleToTexture("tiles_new_world1_b_120_Sprite.png");
		m_fStartCal = float4{ 3.f,60.f };
		m_fEndCal = float4{ 5.f,55.f };
		break;
	}
	case TileDeg::Deg135:
	{
		m_pRender->SetScaleToTexture("tiles_new_world1_b_135_Sprite.png");
		m_fStartCal = float4{ 9.f,60.f };
		m_fEndCal = float4{ 2.5f,74.5f };
		break;
	}
	case TileDeg::Deg225:
	{
		m_pRender->SetScaleToTexture("tiles_new_world1_b_135_Sprite.png");
		//m_pRender->SetFlipY();
		m_fStartCal = float4{ 9.f,27.f };
		m_fEndCal = float4{ 59.f,148.f };
		break;
	}
	case TileDeg::Deg240:
	{
		m_pRender->SetScaleToTexture("tiles_new_world1_b_120_Sprite.png");
		//m_pRender->SetFlipY();
		m_fStartCal = float4{ 3.f,27.f };
		m_fEndCal = float4{ 75.f,151.f };
		break;
	}
	case TileDeg::Deg270:
	{
		m_pRender->SetScaleToTexture("tiles_new_world1_b_90_Sprite.png");
		//m_pRender->SetFlipY();
		m_fStartCal = float4{ 3.f,27.f };
		m_fEndCal = float4{ 119.f,142.f };
		break;
	}
	case TileDeg::Deg300:
	{
		m_pRender->SetScaleToTexture("tiles_new_world1_b_60_Sprite.png");
		//m_pRender->SetFlipY();
		m_fStartCal = float4{ 3.f,60.f };
		m_fEndCal = float4{ 149,145.f };
		break;
	}
	case TileDeg::Deg315:
	{
		m_pRender->SetScaleToTexture("tiles_new_world1_b_45_Sprite.png");
		//m_pRender->SetFlipY();
		m_fStartCal = { 3.f,27.f };
		m_fEndCal = { 158.f,92.5f };
		break;
	}
	case TileDeg::Square:
	{
		m_pRender->SetScaleToTexture("tile_cls_square_Sprite.png");
		m_pCollision = CreateComponent<GameEngineCollision>(ColNum::TILE);
		m_pCollision->GetTransform()->SetLocalScale({ 80.f,80.f,0.f });
		return;
	}	
	case TileDeg::Blank:
	{
		m_pRender->SetScaleToTexture("nothing.png");
		return;
	}
	default:
		MsgAssert("없는 각도");
		break;
	}

	

	PivotCal(static_cast<float>(_TileDeg));



	//std::shared_ptr< GameEngineSpriteRenderer> m_ptestPivot = CreateComponent<GameEngineSpriteRenderer> OrderNum::PLANET);
	//m_ptestPivot->GetTransform()->SetLocalScale(float4(20.f, 20.f));
	//m_ptestPivot->GetTransform()->SetLocalPosition(GetPivotPos());
}


void Tiles::PivotCal(float _Deg)
{
	if (_Deg >= 225)
	{
		m_pRender->GetTransform()->SetLocalRotation({ 180.f,0.f });
	}

	m_fEndCal.RotaitonZDegReturn(_Deg);

	//float4 XCal = { 0.f,41.f };
	//float4 YCal = XCal.RotaitonZDegReturn(360.f - static_cast<float>(_Deg));
	//m_fStartCal += XCal;
	//m_fEndCal += YCal;

	float fabsRenderScaleX = fabs(m_pRender->GetTransform()->GetLocalScale().hx());
	float fabsRenderScaleY = fabs(m_pRender->GetTransform()->GetLocalScale().hy());
	float4 fabsRenderScale = { fabsRenderScaleX ,fabsRenderScaleY };

	m_fStartBetPos = GetTransform()->GetLocalPosition() - fabsRenderScale + m_fStartCal;
	m_fStartBetPos.y = -m_fStartBetPos.y;
	m_pStartPivot->GetTransform()->SetLocalPosition(m_fStartBetPos);

	m_fEndBetPos = m_fEndCal - m_fStartCal;
	m_fEndBetPos.y = -m_fEndBetPos.y;
	m_pEndPivot->GetTransform()->SetLocalPosition(m_pStartPivot->GetTransform()->GetLocalPosition() + m_fEndBetPos);

}

