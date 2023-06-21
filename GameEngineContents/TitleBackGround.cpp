#include "PrecompileHeader.h"
#include "TitleBackGround.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

TitleBackGround::TitleBackGround() 
{
}

TitleBackGround::~TitleBackGround() 
{
}

void TitleBackGround::Start()
{
	m_pRender = CreateComponent<GameEngineSpriteRenderer>(OrderNum::BACKGROUND);
	m_pRender->SetTexture("world1_newsky.png");
	m_pRender->GetTransform()->SetLocalScale(GameEngineWindow::GetScreenSize());
}

void TitleBackGround::Update(float _DeltaTime)
{
}

