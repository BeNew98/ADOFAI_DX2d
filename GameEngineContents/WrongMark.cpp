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
	m_pFontRenderer->GetTransform()->AddLocalPosition({0.f,100.f});
	m_pFontRenderer->SetFont("godoMaum");
	m_pFontRenderer->SetScale(75.f);
	m_pFontRenderer->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);
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
	m_f4Color.a = m_fAlpha;
	m_pFontRenderer->SetColor(m_f4Color);
}

