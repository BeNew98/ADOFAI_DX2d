#include "PrecompileHeader.h"
#include "Planet.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
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
		std::shared_ptr<GameEngineSpriteRenderer> render = CreateComponent<GameEngineSpriteRenderer>(OrderNum::PLANET);
		render->SetTexture("ballsprites_blue_sheet_grid_0_Sprite.png");
		render->GetTransform()->SetLocalScale({ 64.f, 64.f, 0.f });

		std::shared_ptr<GameEngineCollision> m_pCollision = CreateComponent<GameEngineCollision>(OrderNum::PLANET);
		m_pCollision->GetTransform()->SetLocalScale({ 64.f, 64.f, 0.f });
		m_iUseCount += render.use_count();
	}
	else
	{
		std::shared_ptr<GameEngineSpriteRenderer> render = CreateComponent<GameEngineSpriteRenderer>(OrderNum::PLANET);
		render->SetTexture("ballsprites_red_sheet_grid_0_Sprite.png");
		render->GetTransform()->SetLocalScale({ 64.f, 64.f, 0.f });
		std::shared_ptr<GameEngineCollision> m_pCollision = CreateComponent<GameEngineCollision>(OrderNum::PLANET);
		m_pCollision->GetTransform()->SetLocalScale({ 64.f, 64.f, 0.f });
		m_iUseCount += render.use_count();
	}
}

