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
	m_pRender->SetTexture("bottomglow_E2.png");
	m_pRender->GetTransform()->SetLocalScale({300.f,300.f,1.f});
}

