#include "PrecompileHeader.h"
#include "SquareGlowEffect.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTransform.h>
#include <GameEngineCore/GameEngineLevel.h>

#include "EditGui.h"
#include "Tiles.h"
#include "TitleLevel.h"

SquareGlowEffect::SquareGlowEffect() 
{
}

SquareGlowEffect::~SquareGlowEffect() 
{
}


void SquareGlowEffect::Start()
{
	m_fSpeed = EditGui::Editor->GetStageInfo(0).RotSpeed*2.f;
	m_pRender = CreateComponent<GameEngineSpriteRenderer>(OrderNum::EFFECT);
	m_pRender->SetScaleToTexture("topglow_E.png");
}

void SquareGlowEffect::Update(float _DeltaTime)
{
	std::weak_ptr<TitleLevel> Level = GetLevel()->DynamicThis<TitleLevel>();
	if (Level.lock()->GetTime() >= m_fSpeed)
	{
		m_bColor = Level.lock()->GetGlowValue();
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
	else if (m_iIndex % 2 == 1)
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

