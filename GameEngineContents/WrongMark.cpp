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


	m_pFontRenderer = CreateComponent<GameEngineFontRenderer>(OrderNum::EFFECT);
	m_pFontRenderer->GetTransform()->AddLocalPosition({0.f,200.f});
	m_pFontRenderer->SetFont("Ch2.0 - 1");
	m_pFontRenderer->SetScale(100.f);
}

void WrongMark::Update(float _DeltaTime)
{
	if (m_fAlpha<=0.f)
	{
		Death();
	}
	m_fAlpha -= _DeltaTime;
	m_pRender->ColorOptionValue.MulColor = { 1.f,1.f,1.f,m_fAlpha };
}

