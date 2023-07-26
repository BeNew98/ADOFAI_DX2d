#include "PrecompileHeader.h"
#include "BgmSpeed.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineCollision.h>

#include "Planet.h"
#include "PlayLevel.h"

BgmSpeed::BgmSpeed() 
{
}

BgmSpeed::~BgmSpeed() 
{
}

void BgmSpeed::SetType(BpmType _Type)
{
	m_eType = _Type;

	switch (m_eType)
	{
	case BpmType::NONE:
	{
		m_pRenderer->SetTexture("nothing.png");
	}
	break;
	case BpmType::RABBIT:
	{
		m_pRenderer->SetTexture("tile_rabbit_light_new0_Sprite.png");
	}
	break;
	case BpmType::SNAIL:
	{
		m_pRenderer->SetTexture("tile_snail_light_new0_Sprite.png");
	}
	break;
	case BpmType::DOUBLE_RABBIT:
	{
		m_pRenderer->SetTexture("tile_rabbit_double_light_new0_Sprite.png");
	}
	break;
	case BpmType::DOUBLE_SNAIL:
	{
		m_pRenderer->SetTexture("tile_snail_double_light_new0_Sprite.png");
	}
	break;
	}
}

void BgmSpeed::Start()
{
	m_pRenderer = CreateComponent<GameEngineSpriteRenderer>(OrderNum::EFFECT);
	m_pRenderer->GetTransform()->SetWorldScale({ 64.f, 64.f, 1.f });

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
			std::shared_ptr<PlayLevel> pPlayLevel = GetLevel()->DynamicThis<PlayLevel>();
			if (pPlanet->IsCenter() == true && m_eType != BpmType::NONE&& m_bTrigger == false&& pPlayLevel->GetGameEnd() == false)
			{
				switch (m_eType)
				{
				case BpmType::NONE:
				{
					m_bTrigger = true;
					GlobalValue::GetInst()->BPM = 1.f;
				}
					break;
				case BpmType::RABBIT:
				{
					m_bTrigger = true;
					GlobalValue::GetInst()->BPM = 2.f;
				}
					break;
				case BpmType::SNAIL:
				{
					m_bTrigger = true;
					GlobalValue::GetInst()->BPM = 0.5f;
				}
					break;
				case BpmType::DOUBLE_RABBIT:
				{
					m_bTrigger = true;
					GlobalValue::GetInst()->BPM = 4.f;
				}
					break;
				case BpmType::DOUBLE_SNAIL:
				{
					m_bTrigger = true;
					GlobalValue::GetInst()->BPM = 0.25f;
				}
					break;
				default:
					break;
				}
			}
		}
	}
}

