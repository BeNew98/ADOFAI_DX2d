#include "PrecompileHeader.h"
#include "BlackScreen.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

BlackScreen::BlackScreen() 
{
}

BlackScreen::~BlackScreen() 
{	
}

void BlackScreen::Start()
{
	std::shared_ptr<GameEngineSpriteRenderer> render = CreateComponent<GameEngineSpriteRenderer>();
	render->SetScaleToTexture("BlackScreen.png");
}

