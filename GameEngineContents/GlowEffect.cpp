#include "PrecompileHeader.h"
#include "GlowEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTransform.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Tiles.h"
#include "TitleLevel.h"

GlowEffect::GlowEffect() 
{
}

GlowEffect::~GlowEffect() 
{
}


void GlowEffect::Start()
{
	m_pRender = CreateComponent<GameEngineSpriteRenderer>(OrderNum::EFFECT);
	m_pRender->SetScaleToTexture("bottomglow_E2.png");
}

void GlowEffect::Update(float _DeltaTime)
{
	if (m_sType == GlowType::ROUND)
	{
		return;
	}
	std::weak_ptr<TitleLevel> Level = GetLevel()->DynamicThis<TitleLevel>();
	if (Level.lock()->GetTime() >=360.f)
	{
		Level.lock()->AddTime(-360.f);
		m_bColor = !m_bColor;
 		m_bCheckValue = true;
	}
	if (false == m_bCheckValue)
	{
		return;
	}
	
	if (m_iIndex%2 == 0)
	{
		if (true== m_bColor)
		{
			m_pRender->SetScaleToTexture("topglow_E.png");
		}
		else
		{
			m_pRender->SetScaleToTexture("topglow_F.png");
		}

	}

	if (m_iIndex % 2 == 1)
	{
		if (false == m_bColor)
		{
			m_pRender->SetScaleToTexture("topglow_E.png");
		}
		else
		{
			m_pRender->SetScaleToTexture("topglow_F.png");
		}

	}
	m_bCheckValue = false;
}

