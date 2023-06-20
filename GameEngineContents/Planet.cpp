#include "PrecompileHeader.h"
#include "Planet.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "EditGui.h"

int Planet::m_iUseCount = 0;

Planet::Planet()
{
}

Planet::~Planet() 
{
}
 

void Planet::CreateEffect()
{
}

void Planet::Start()
{
	std::shared_ptr<GameEngineSpriteRenderer> render = CreateComponent<GameEngineSpriteRenderer>(OrderNum::PLANET);
	render->GetTransform()->SetLocalScale({ 64.f, 64.f, 1.f });

	m_fSpeed = EditGui::Editor->GetStageInfo(0).RotSpeed;
	m_pCollision = CreateComponent<GameEngineCollision>(ColNum::PLANET);
	m_pCollision->GetTransform()->SetLocalScale({ 64.f, 64.f, 1.f });
	if (m_iUseCount!=0)
	{
		render->SetTexture("ballsprites_blue_sheet_grid_0_Sprite.png");
		m_iUseCount = 0;

	}
	else
	{
		render->SetTexture("ballsprites_red_sheet_grid_0_Sprite.png");
		m_bCenter = true;
		++m_iUseCount;
	}


	//GetTransform()->SetLocalScale({ 64.f, 64.f, 1.f });
}

void Planet::Update(float _DeltaTime)
{
	if (m_bCenter==true)
	{
		GetTransform()->AddLocalRotation({ 0.f,0.f,-m_fSpeed * _DeltaTime });
	}
}

