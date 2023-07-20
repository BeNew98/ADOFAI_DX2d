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
	//m_pFontRenderer->SetFont("Ch2.0-1");
	m_pFontRenderer->SetFont("godoMaum");
	m_pFontRenderer->SetScale(m_fScale);
	m_pFontRenderer->SetColor(float4::White);
	m_pFontRenderer->SetFontFlag(FW1_TEXT_FLAG::FW1_CENTER);
}

void TextObj::Update(float _DeltaTime)
{
	if (m_bAlpha == false)
	{
		return;
	}

	m_fAlpha -= _DeltaTime;

	if (m_fAlpha <= 0.f)
	{
		m_fAlpha = 0.f;
		Death();
	}

	m_f4Color.a = m_fAlpha;
	m_pFontRenderer->SetColor(m_f4Color);
}

