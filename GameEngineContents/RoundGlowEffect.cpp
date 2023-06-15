#include "PrecompileHeader.h"
#include "RoundGlowEffect.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

RoundGlowEffect::RoundGlowEffect() 
{
}

RoundGlowEffect::~RoundGlowEffect() 
{
}

void RoundGlowEffect::Start()
{
	m_pRender = CreateComponent<GameEngineSpriteRenderer>(OrderNum::EFFECT);
	m_pRender->SetScaleToTexture("bottomglow_E2.png");
}

