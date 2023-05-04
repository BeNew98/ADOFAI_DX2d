#include "PrecompileHeader.h"
#include "TitleLogo.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineRenderer.h>

TitleLogo::TitleLogo() 
{
}

TitleLogo::~TitleLogo() 
{
}

void TitleLogo::Start()
{
	std::shared_ptr<GameEngineSpriteRenderer> Render0 = CreateComponent<GameEngineSpriteRenderer>();
	Render0->SetScaleToTexture("logo_text_Sprite.png");


	std::shared_ptr<GameEngineSpriteRenderer> Render1 = CreateComponent<GameEngineSpriteRenderer>();
	Render1->SetScaleToTexture("logo_text_shadow_Sprite.png");
}

