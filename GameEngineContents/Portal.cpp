#include "PrecompileHeader.h"
#include "Portal.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Planet.h"
#include "TextObj.h"
Portal::Portal() 
{
}

Portal::~Portal() 
{
}

void Portal::Start()
{
	m_pEffect = CreateComponent<GameEngineSpriteRenderer>(OrderNum::MAP);
	m_pEffect->SetScaleToTexture("Portal_Effect.png");
	
	m_pEffect->ColorOptionValue.PlusColor = float4{ 138.f / 255.f, 51.f / 255.f, 178.f / 255.f,0.f };
	m_pEffect->ColorOptionValue.MulColor = float4{ 138.f / 255.f, 51.f / 255.f, 178.f / 255.f ,1.f};
	//m_pEffect->GetTransform()->SetLocalScale({ 64.f,64.f ,1.f });

	std::shared_ptr<GameEngineSpriteRenderer> pRender = CreateComponent<GameEngineSpriteRenderer>(OrderNum::MAP);
	pRender->SetTexture("tiles_portal_circle_new_inner_Sprite.png");
	pRender->GetTransform()->SetLocalScale({ 64.f,64.f ,1.f});
	pRender->ColorOptionValue.PlusColor = float4{ 187.f / 255.f, 202.f / 255.f, 204.f / 255.f,0.f };
	pRender->ColorOptionValue.MulColor = float4{ 187.f / 255.f, 202.f / 255.f, 204.f / 255.f,1.f };

	m_pCollision = CreateComponent< GameEngineCollision>(ColNum::PORTAL);
	m_pCollision->GetTransform()->SetLocalScale({ 64.f, 64.f,1.f});

	m_pAccuracyCol = CreateComponent< GameEngineCollision>(ColNum::PORTAL);
	m_pAccuracyCol->GetTransform()->SetLocalScale({ 64.f, 64.f,1.f });
	m_pAccuracyCol->GetTransform()->SetLocalPosition(float4{ 0.f,-100.f });
}

void Portal::Update(float _DeltaTime)
{
	std::shared_ptr<GameEngineCollision> pColPlanet = m_pCollision->Collision(ColNum::PLANET);
	m_pEffect->GetTransform()->AddLocalRotation(float4{ 0.f,0.f,_DeltaTime * 360.f });
	if (nullptr != pColPlanet)
	{

		std::shared_ptr<Planet> pPlanet = pColPlanet->GetActor()->DynamicThis<Planet>();
		if (nullptr != pPlanet)
		{

			if (pPlanet->IsCenter() == true && m_Ptr != nullptr && false == m_EventTrigger)
			{
				m_Ptr();
				m_Ptr = nullptr;
				m_EventTrigger = true;
			}
		}
	}
	std::shared_ptr<GameEngineCollision> pColAcc = m_pAccuracyCol->Collision(ColNum::PLANET);

	if (nullptr != pColAcc)
	{
		std::shared_ptr<Planet> pPlanet2 = pColAcc->GetActor()->DynamicThis<Planet>();
		if (nullptr != pPlanet2)
		{

			if (pPlanet2->IsCenter() == true && m_pText != nullptr /*&& false == m_EventTrigger2*/)
			{
				if (m_fTextTime >= 1.f)
				{
					m_fTextTime = 1.f;
					m_pText->SetColor({ 255.f ,255.f ,255.f , 255.f * m_fTextTime });
					return;
				}
				m_fTextTime += _DeltaTime;
				//m_pText->On();
				m_pText->SetColor({ 255.f ,255.f ,255.f , 255.f * m_fTextTime });
			}

		}
	}
	else if (nullptr != pColAcc)
	{
		std::shared_ptr<Planet> pPlanet2 = pColAcc->GetActor()->DynamicThis<Planet>();
		if (nullptr != pPlanet2)
		{

			if (pPlanet2->IsCenter() == false && m_pText != nullptr)
			{
				if (m_pText != nullptr /*&& true == m_EventTrigger2*/)
				{
					if (m_fTextTime <= 0.f)
					{
						m_fTextTime = 0.f;
						m_pText->SetColor({ 255.f,255.f ,255.f , 255.f * m_fTextTime });
						return;
						//m_EventTrigger2 = false;
					}
					m_fTextTime -= _DeltaTime;
					m_pText->SetColor({ 255.f,255.f ,255.f , 255.f * m_fTextTime });
				}
			}
		}
	}
	else
	{
		if (m_pText != nullptr /*&& true == m_EventTrigger2*/)
		{
			if (m_fTextTime <= 0.f)
			{
				m_fTextTime = 0.f;
				m_pText->SetColor({ 255.f,255.f ,255.f , 255.f * m_fTextTime });
				return;
				//m_EventTrigger2 = false;
			}
			m_fTextTime -= _DeltaTime;
			m_pText->SetColor({ 255.f,255.f ,255.f , 255.f * m_fTextTime });
		}
	}
}
