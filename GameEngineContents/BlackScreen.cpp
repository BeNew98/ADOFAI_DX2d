#include "PrecompileHeader.h"
#include "BlackScreen.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "BackGroundRenderer.h"

BlackScreen::BlackScreen() 
{
}

BlackScreen::~BlackScreen() 
{	
}

void BlackScreen::Start()
{
	std::shared_ptr<BackGroundRenderer> render = CreateComponent<BackGroundRenderer>(OrderNum::BACKGROUND);
	render->SetScaleToTexture("BlackScreen.png");
}

void BlackScreen::Update(float _DeltaTime)
{
}

