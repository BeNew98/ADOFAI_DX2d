#include "PrecompileHeader.h"
#include "SmokeEffect.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

SmokeEffect::SmokeEffect() 
{
}

SmokeEffect::~SmokeEffect() 
{
}

void SmokeEffect::SetColor(float4 _Color)
{
	m_pRender->ColorOptionValue.PlusColor = _Color;
	m_pRender->ColorOptionValue.PlusColor.w = 0.f;
	m_pRender->ColorOptionValue.MulColor = _Color;
	m_pRender->ColorOptionValue.MulColor.w = 0.85f;
}

void SmokeEffect::Start()
{
	m_pRender = CreateComponent< GameEngineSpriteRenderer>(OrderNum::EFFECT);
	m_pRender->SetTexture("smokeA.png");
	m_pRender->GetTransform()->SetLocalScale(float4(64.f, 64.f, 1.f, 1.f));
}

void SmokeEffect::Update(float _DeltaTime)
{
	m_fTime += _DeltaTime;
	if (0.05f<= m_fTime)
	{
		if (m_fRatio <= 0.f)
		{
			Death();
		}
		float4 f4Scale = m_pRender->GetTransform()->GetLocalScale();
		m_pRender->GetTransform()->SetLocalScale(float4(f4Scale.x* m_fRatio, f4Scale.y* m_fRatio,1.f,1.f));
		m_fRatio -= 0.05f;
		m_fTime -= 0.05f;
	}
}

