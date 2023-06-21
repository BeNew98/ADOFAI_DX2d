#include "PrecompileHeader.h"
#include "TextObj.h"

#include <GameEngineCore/GameEngineFontRenderer.h>

TextObj::TextObj() 
{
}

TextObj::~TextObj() 
{
}

void TextObj::Start()
{
	m_pFontRenderer = CreateComponent<GameEngineFontRenderer>(OrderNum::TEXT);
	m_pFontRenderer->GetTransform()->AddLocalPosition({ 0.f,0.f });
	m_pFontRenderer->SetFont("Ch2.0-1");
	m_pFontRenderer->SetScale(200.f);
}

void TextObj::Update(float _DeltaTime)
{
	m_fAlpha -= _DeltaTime;

	if (m_fAlpha <= 0.f)
	{
		m_fAlpha = 0.f;
		Death();
	}
	float4 f4FontColor = float4::White;
	f4FontColor.a = m_fAlpha;
	m_pFontRenderer->SetColor(f4FontColor);
}

