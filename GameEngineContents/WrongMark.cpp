#include "PrecompileHeader.h"
#include "WrongMark.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

WrongMark::WrongMark() 
{
}

WrongMark::~WrongMark() 
{
}

void WrongMark::Start()
{
	m_pRender = CreateComponent<GameEngineSpriteRenderer>(OrderNum::MAP);
	m_pRender->SetScaleToTexture("create_tile_direction_x_Sprite.png");


	m_pFontRenderer = CreateComponent<GameEngineFontRenderer>(OrderNum::TEXT);
	m_pFontRenderer->GetTransform()->AddLocalPosition({-100.f,100.f});
	m_pFontRenderer->SetFont("Ch2.0-1");
	m_pFontRenderer->SetScale(75.f);
}

void WrongMark::Update(float _DeltaTime)
{	
	m_fAlpha -= _DeltaTime;

	if (m_fAlpha <= 0.f)
	{
		m_fAlpha = 0.f;
		Death();
	}
	m_pRender->ColorOptionValue.MulColor = { 1.f,1.f,1.f,m_fAlpha };
	float4 f4FontColor = m_pFontRenderer->GetColor();
	f4FontColor.a = m_fAlpha;
	m_pFontRenderer->SetColor(f4FontColor);
}

