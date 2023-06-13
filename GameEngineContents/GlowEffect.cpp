#include "PrecompileHeader.h"
#include "GlowEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTransform.h>
#include "Tiles.h"

GlowEffect::GlowEffect() 
{
}

GlowEffect::~GlowEffect() 
{
}

void GlowEffect::Start()
{
	m_pRender = CreateComponent<GameEngineSpriteRenderer>(OrderNum::EFFECT);
	m_pRender->SetScaleToTexture("bottomglow_E2.png");
}

void GlowEffect::Update(float _DeltaTime)
{
	switch (m_sDeg)
	{
	case TileDeg::Deg0:
		
	case TileDeg::Deg45:
		
	case TileDeg::Deg60:
		
	case TileDeg::Deg90:
		
	case TileDeg::Deg120:
		
	case TileDeg::Deg135:
		
	case TileDeg::Deg225:
		
	case TileDeg::Deg240:
		
	case TileDeg::Deg270:
		
	case TileDeg::Deg300:
		
	case TileDeg::Deg315:
		break;
	case TileDeg::Square:
		break;
	case TileDeg::Blank:
		break;
	default:
		break;
	}
}

