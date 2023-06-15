#include "PrecompileHeader.h"
#include "TitleLogo.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineRenderer.h>

TitleLogo::TitleLogo() 
{
}

TitleLogo::~TitleLogo() 
{
}

void TitleLogo::Start()
{
	m_pLogo= CreateComponent<GameEngineSpriteRenderer>();
	m_pLogo->SetScaleToTexture("logo_text_Sprite.png");

	m_pLogoShadow = CreateComponent<GameEngineSpriteRenderer>();
	m_pLogoShadow->SetScaleToTexture("logo_text_shadow_Sprite.png");
}

void TitleLogo::Update(float _DeltaTime)
{
	if (m_bAlpha == false)
	{
		if (m_fAlpha <= 0.f)
		{
			return;
		}
		m_fAlpha -= _DeltaTime / 0.3f;
		m_pLogo->ColorOptionValue.MulColor = { 1.f,1.f,1.f,m_fAlpha };
		m_pLogoShadow->ColorOptionValue.MulColor = { 1.f,1.f,1.f,m_fAlpha };
	}
	else
	{
		if (m_fAlpha >= 1.f)
		{
			return;
		}
		m_fAlpha += _DeltaTime / 0.3f;
		m_pLogo->ColorOptionValue.MulColor = { 1.f,1.f,1.f,m_fAlpha };
		m_pLogoShadow->ColorOptionValue.MulColor = { 1.f,1.f,1.f,m_fAlpha };
	}
}

