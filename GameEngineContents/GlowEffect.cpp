#include "PrecompileHeader.h"
#include "GlowEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

GlowEffect::GlowEffect() 
{
}

GlowEffect::~GlowEffect() 
{
}

void GlowEffect::Start()
{
	std::shared_ptr<GameEngineSpriteRenderer> render = CreateComponent<GameEngineSpriteRenderer>(OrderNum::EFFECT);
	render->SetScaleToTexture("bottomglow_E2.png");
}

