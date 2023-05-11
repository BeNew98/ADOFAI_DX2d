#include "PrecompileHeader.h"
#include "Planet.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>

Planet::Planet()
{
}

Planet::~Planet() 
{
}

int Planet::m_iUseCount = 0; 

void Planet::Start()
{
	if (m_iUseCount!=0)
	{
		std::shared_ptr<GameEngineSpriteRenderer> render = CreateComponent<GameEngineSpriteRenderer>();
		render->SetScaleToTexture("ballsprites_blue_sheet_grid_0_Sprite.png");
		m_iUseCount += render.use_count();
	}
	else
	{
		std::shared_ptr<GameEngineSpriteRenderer> render = CreateComponent<GameEngineSpriteRenderer>();
		render->SetScaleToTexture("ballsprites_red_sheet_grid_0_Sprite.png");
		m_iUseCount += render.use_count();
	}
}

