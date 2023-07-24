#include "PrecompileHeader.h"
#include "BgmSpeed.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Planet.h"

BgmSpeed::BgmSpeed() 
{
}

BgmSpeed::~BgmSpeed() 
{
}

void BgmSpeed::Start()
{
	m_pRenderer = CreateComponent<GameEngineSpriteRenderer>(OrderNum::EFFECT);

	m_pCollision = CreateComponent<GameEngineCollision>(OrderNum::EFFECT);;
	m_pCollision->GetTransform()->SetWorldScale({ 64.f, 64.f, 1.f });
}

void BgmSpeed::Update(float _DeltaTime)
{
	if (true == m_bTrigger)
	{
		return;
	}
	std::shared_ptr<GameEngineCollision> pColPlanet = m_pCollision->Collision(ColNum::PLANET);
	if (nullptr != pColPlanet)
	{

		std::shared_ptr<Planet> pPlanet = pColPlanet->GetActor()->DynamicThis<Planet>();
		if (nullptr != pPlanet)
		{

			if (pPlanet->IsCenter() == true && m_eType != BpmType::NONE&& m_bTrigger == false)
			{
				switch (m_eType)
				{
				case BpmType::NONE:
					break;
				case BpmType::RABBIT:
					break;
				case BpmType::SNAIL:
					break;
				case BpmType::DOUBLE_RABBIT:
					break;
				case BpmType::DOUBLE_SNAIL:
					break;
				default:
					break;
				}
			}
		}
	}
}

