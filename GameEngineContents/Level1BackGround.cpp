#include "PrecompileHeader.h"
#include "Level1BackGround.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include "BackGroundRenderer.h"

Level1BackGround::Level1BackGround() 
{
}

Level1BackGround::~Level1BackGround() 
{
}

void Level1BackGround::Start()
{
	std::shared_ptr<BackGroundRenderer> render = CreateComponent<BackGroundRenderer>(OrderNum::BACKGROUND);
	render->SetScaleToTexture("testback.png");
}

