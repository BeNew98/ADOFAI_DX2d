#include "PrecompileHeader.h"
#include "Portal.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "Planet.h"
Portal::Portal() 
{
}

Portal::~Portal() 
{
}

void Portal::Start()
{
	std::shared_ptr<GameEngineSpriteRenderer> pRender = CreateComponent<GameEngineSpriteRenderer>(OrderNum::MAP);
	pRender->SetTexture("tiles_portal_circle_new_inner_Sprite.png");
	pRender->GetTransform()->SetLocalScale({ 64.f,64.f });

	m_pCollision = CreateComponent< GameEngineCollision>(ColNum::PORTAL);
	m_pCollision->GetTransform()->SetLocalScale({ 64.f, 64.f});
}

void Portal::Update(float _DeltaTime)
{
	std::shared_ptr<GameEngineCollision> pColPlanet = m_pCollision->Collision(ColNum::PLANET);

	if (nullptr == pColPlanet)
	{
		return;
	}
	std::shared_ptr<Planet> pPlanet = pColPlanet->GetActor()->DynamicThis<Planet>();
	if (nullptr == pPlanet)
	{
		return;
	}
	if (pPlanet->IsCenter() == true && m_Ptr != nullptr && false == m_EventTrigger)
	{
		m_Ptr();
		m_Ptr = nullptr;
		m_EventTrigger = true;
	}
}

