#include "PrecompileHeader.h"
#include "BlackScreen.h"

#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineLevel.h>

BlackScreen::BlackScreen() 
{
}

BlackScreen::~BlackScreen() 
{
}

void BlackScreen::Start()
{
	m_pRender = CreateComponent<GameEngineSpriteRenderer>(OrderNum::BACKGROUND);
	m_pRender->SetTexture("BlackScreen.png");

	m_pRender->GetTransform()->SetLocalScale(GameEngineWindow::GetScreenSize() * 1.2f);
}

void BlackScreen::Update(float _DeltaTime)
{
	GetTransform()->SetLocalPosition(GetLevel()->GetMainCamera()->GetTransform()->GetLocalPosition());
}

