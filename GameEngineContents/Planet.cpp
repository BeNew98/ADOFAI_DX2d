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
	m_fScaleRatio = m_fDistance / 60.f * EditGui::Editor->GetStageInfo(0).BPM;
	m_pCollision = CreateComponent<GameEngineCollision>(ColNum::PLANET);
	m_pCollision->GetTransform()->SetLocalScale({ 64.f, 64.f, 1.f });
	m_pRing = CreateComponent<GameEngineSpriteRenderer>(OrderNum::EFFECT);
	m_pRing->SetTexture("white-ring.png");
	//m_pRing->GetTransform()->SetLocalScale({ m_fDistance*2.f,m_fDistance*2.f,1.f });

	if (m_iUseCount != 0)
	{
		render->SetTexture("ballsprites_blue_sheet_grid_0_Sprite.png");
		m_iUseCount = 0;
		m_bCenter = false;
		m_pRing->ColorOptionValue.PlusColor = float4{ 0.f, 0.f,1.f ,0.f };
		m_pRing->ColorOptionValue.MulColor = float4{ 0.f, 0.f,1.f,0.35f };

	}
	else
	{
		render->SetTexture("ballsprites_red_sheet_grid_0_Sprite.png");
		m_bCenter = true;
		++m_iUseCount;

		m_pRing->ColorOptionValue.PlusColor = float4{ 1.f, 0.f, 0.f ,0.f };
		m_pRing->ColorOptionValue.MulColor = float4{ 1.f, 0.f,0.f,0.35f };
	}


	//GetTransform()->SetLocalScale({ 64.f, 64.f, 1.f });
}

void Planet::Update(float _DeltaTime)
{
	if (m_GameStart == false)
	{
		return;
	}
	if (m_bCenter==true)
	{
		GetTransform()->AddLocalRotation({ 0.f,0.f,-m_fSpeed * _DeltaTime });
		m_pRing->GetTransform()->AddWorldRotation({ 0.f,0.f,-m_fSpeed * _DeltaTime / 6.f });
		if (m_pRing->GetTransform()->GetLocalScale().x >= m_fDistance * 2.f)
		{
			return;
		}
		m_pRing->GetTransform()->AddLocalScale(float4{ m_fScaleRatio ,m_fScaleRatio ,0.f,0.f }*_DeltaTime*2.f);
	}
	else
	{
		if (m_pRing->GetTransform()->GetLocalScale().x<=64.f)
		{
			return;
		}
		m_pRing->GetTransform()->AddLocalScale(-float4{ m_fScaleRatio ,m_fScaleRatio ,0.f,0.f}*_DeltaTime * 2.f);
		int a = 0;
	}
}

